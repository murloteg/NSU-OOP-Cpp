#include "SoundController.h"

SoundController::SoundController(std::vector<std::string> wavFileNames, std::string configFileName)
{
    wavFileNames_ = wavFileNames;
    parserWav_ = ParserWAVHeader(wavFileNames_[1]);
    parserWav_.parseWAVHeader();
    configFile_ = ConfigFile(configFileName);
    configFile_.parseFile();
    convertersNumber_ = configFile_.getNumberOfConverters();
    bufferOfSamples_.resize(parserWav_.getByteRate());
    additionalBufferOfSamples_.resize(parserWav_.getByteRate());
    wavHeader_.resize(parserWav_.getByteRate());
    startingPreparations();
    currentConverterNumber_ = 0;
    currentSecondsInFile_ = 0;
    isEndOfFile_ = false;
    nextConverter_ = nullptr;
}

void SoundController::conversion()
{
    while (currentConverterNumber_ < convertersNumber_)
    {
        putHeaderInOutput();
        getNextConverter();
        while (!isEndOfFile_)
        {
            getNextBufferData();
            int numberOfAdditionalWAV = configFile_.getAdditionalWAVNumbers();
            if (numberOfAdditionalWAV != UNDEFINED)
            {
                getNextDataForAdditionalBuffer(numberOfAdditionalWAV);
            }
            nextConverter_->conversion(bufferOfSamples_, additionalBufferOfSamples_, currentSecondsInFile_);
            putDataInOutput();
            ++currentSecondsInFile_;
        }

        configFile_.increaseCurrentCommandIndex();
        currentSecondsInFile_ = 0;
        isEndOfFile_ = false;
        resetFileFlags();
        clearVectors();
        ++currentConverterNumber_;
    }
    prepareFinallyOutput();
}

void SoundController::getNextConverter()
{
    nextConverterName_ = configFile_.getNextCommandAndPrepareArguments();
    toUpperCase(nextConverterName_);
    try
    {
        nextConverter_ = ConverterFactory::createConverter(nextConverterName_, parserWav_.getByteRate(),
                                                           configFile_.getFirstParameter(),
                                                           configFile_.getSecondParameter());
        if (nextConverter_ == nullptr)
        {
            throw std::invalid_argument("invalid command in configuration file");
        }
    }
    catch (std::exception& exception)
    {
        exception.what();
    }
}

void SoundController::clearVectors()
{
    bufferOfSamples_.clear();
    additionalBufferOfSamples_.clear();
    bufferOfSamples_.resize(parserWav_.getByteRate());
    additionalBufferOfSamples_.resize(parserWav_.getByteRate());
}

void SoundController::resetFileFlags()
{
    input_.open(firstStoragePath_, std::fstream::in);
    output_.open(secondStoragePath_, std::fstream::in);
    input_.clear();
    output_.clear();
    input_.seekg(0, std::ios::beg);
    output_.seekg(0, std::ios::beg);
    input_.close();
    output_.close();
}

void SoundController::getNextDataForAdditionalBuffer(int numberOfAdditionalWAV)
{
    input_.open("../" + wavFileNames_[numberOfAdditionalWAV], std::fstream::in);
    ParserWAVHeader additionalParserWAV(wavFileNames_[numberOfAdditionalWAV]);
    additionalParserWAV.parseWAVHeader();
    if (input_.is_open())
    {
        input_.seekg(additionalParserWAV.getWAVHeaderLength() + parserWav_.getByteRate() * currentSecondsInFile_, std::ios::beg);
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            if (isEndOfFile_)
            {
                return;
            }

            if (input_.eof())
            {
                additionalBufferOfSamples_[i] = bufferOfSamples_[i];
                continue;
            }
            int characterCode = input_.get();
            additionalBufferOfSamples_[i] = characterCode;
        }
    }
    input_.close();
}

void SoundController::getNextBufferData()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        input_.open(firstStoragePath_, std::fstream::in);
    }
    else
    {
        input_.open(secondStoragePath_, std::fstream::in);
    }

    if (input_.is_open())
    {
        input_.seekg(parserWav_.getWAVHeaderLength() + parserWav_.getByteRate() * currentSecondsInFile_, std::ios::beg);
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            if (input_.eof())
            {
                isEndOfFile_ = true;
                return;
            }
            int characterCode = input_.get();
            bufferOfSamples_[i] = characterCode;
        }
    }
    input_.close();
}

void SoundController::toUpperCase(std::string& string)
{
    for (auto& item : string)
    {
        if ('a' <= item && item <= 'z')
        {
            item -= DIFFERENCE_UPPER_CASE;
        }
    }
}

void SoundController::putHeaderInOutput()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open(secondStoragePath_, std::fstream::out | std::fstream::trunc);
    }
    else
    {
        output_.open(firstStoragePath_, std::fstream::out | std::fstream::trunc);
    }

    if (output_.is_open())
    {
        for (int i = 0; i < parserWav_.getWAVHeaderLength(); ++i)
        {
            output_ << wavHeader_[i];
        }
    }
    output_.close();
}

void SoundController::putDataInOutput()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open(secondStoragePath_, std::fstream::out | std::fstream::app);
    }
    else
    {
        output_.open(firstStoragePath_, std::fstream::out | std::fstream::app);
    }

    if (output_.is_open())
    {
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            output_ << bufferOfSamples_[i];
        }
    }
    output_.close();
}

void SoundController::startingPreparations()
{
    std::fstream result("../" + wavFileNames_[0], std::fstream::out | std::fstream::trunc);
    result.close();
    std::fstream firstWAV("../" + wavFileNames_[1], std::fstream::in);
    input_.open(firstStoragePath_, std::fstream::out | std::fstream::trunc);
    if (firstWAV.is_open())
    {
        int counter = 0;
        while (!firstWAV.eof())
        {
            int characterCode = firstWAV.get();
            if (counter < parserWav_.getWAVHeaderLength())
            {
                wavHeader_[counter] = characterCode;
            }
            input_ << static_cast<char>(characterCode);
            ++counter;
        }
    }
    firstWAV.close();
    input_.close();
}

void SoundController::prepareFinallyOutput()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open(firstStoragePath_, std::fstream::in);
    }
    else
    {
        output_.open(secondStoragePath_, std::fstream::in);
    }
    std::fstream result("../" + wavFileNames_[0], std::fstream::out | std::fstream::trunc);
    if (output_.is_open() && result.is_open())
    {
        while (!output_.eof())
        {
            int characterCode = output_.get();
            result << static_cast<char>(characterCode);
        }
    }
    output_.close();
    result.close();
}

SoundController::~SoundController()
{
    bufferOfSamples_.clear();
    additionalBufferOfSamples_.clear();
    wavHeader_.clear();
    output_.open(firstStoragePath_, std::fstream::out | std::fstream::trunc);
    output_.close();
    output_.open(secondStoragePath_, std::fstream::out | std::fstream::trunc);
    output_.close();
}
