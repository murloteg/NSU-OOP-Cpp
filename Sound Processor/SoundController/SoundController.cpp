#include "SoundController.h"

SoundController::SoundController(std::vector<std::string> wavFileNames, std::string configFileName)
{
    wavFileNames_ = wavFileNames;
    configFileName_ = configFileName;
    currentConverterNumber_ = 0;
    currentSecondsInFile_ = 0;
    isEndOfFile_ = false;
    parserWav_ = ParserWAV(wavFileNames_[1]);
    configFile_ = ConfigFile(configFileName_);
    parserWav_.parseWAV();
    configFile_.parseFile();
    minWAVFileHeaderLength_ = parserWav_.getWAVHeaderLength();
    convertersNumber_ = configFile_.getNumberOfConverters();
    bufferOfSamples_ = new unsigned char [parserWav_.getByteRate()];
    additionalBufferOfSamples_ = new unsigned char [parserWav_.getByteRate()];
    wavHeader_ = new unsigned char [minWAVFileHeaderLength_];
    prepareInputFile();
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
            int numberOfAdditionalWAV = configFile_.getAdditionalWAVNumbers(currentConverterNumber_);
            if (numberOfAdditionalWAV != UNDEFINED)
            {
                getNextDataForAdditionalWAV(numberOfAdditionalWAV);
            }
            nextConverter_->conversion(bufferOfSamples_, additionalBufferOfSamples_, currentSecondsInFile_);
            putDataInOutput();
            ++currentSecondsInFile_;
        }
        configFile_.increaseCurrentCommandIndex_();
        currentSecondsInFile_ = 0;
        isEndOfFile_ = false;
        input_.open("../SoundController/firstStorage.wav", std::fstream::in);
        output_.open("../SoundController/secondStorage.wav", std::fstream::in);
        input_.clear();
        output_.clear();
        input_.close();
        output_.close();
        ++currentConverterNumber_;
    }
    returnFinallyOutput();
}

void SoundController::getNextConverter()
{
    nextConverterName_ = configFile_.prepareAndConvertParameters();
    toUpperCase(nextConverterName_);
    nextConverter_ = ConverterFactory::createConverter(nextConverterName_, parserWav_.getByteRate(),
                                                       configFile_.getFirstParameter(),
                                                       configFile_.getSecondParameter());
}

void SoundController::getNextDataForAdditionalWAV(int numberOfAdditionalWAV)
{
    input_.open("../" + wavFileNames_[numberOfAdditionalWAV], std::fstream::in);
    ParserWAV additionalParser(wavFileNames_[numberOfAdditionalWAV]);
    additionalParser.parseWAV();
    if (input_.is_open())
    {
        input_.seekg(additionalParser.getWAVHeaderLength() + parserWav_.getByteRate() * currentSecondsInFile_, std::fstream::beg);
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
        input_.open("../SoundController/firstStorage.wav", std::fstream::in);
    }
    else
    {
        input_.open("../SoundController/secondStorage.wav", std::fstream::in);
    }

    if (input_.is_open())
    {
        input_.seekg(minWAVFileHeaderLength_ + parserWav_.getByteRate() * currentSecondsInFile_, std::fstream::beg);
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
            item -= 32;
        }
    }
}

void SoundController::putHeaderInOutput()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::trunc);
    }
    else
    {
        output_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    }

    if (output_.is_open())
    {
        for (int i = 0; i < minWAVFileHeaderLength_; ++i)
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
        output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::app);
    }
    else
    {
        output_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::app);
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

void SoundController::prepareInputFile()
{
    for (int i = 0; i < parserWav_.getByteRate(); ++i)
    {
        additionalBufferOfSamples_[i] = 0;
    }
    std::fstream result("../" + wavFileNames_[0], std::fstream::out | std::fstream::trunc);
    result.close();
    std::fstream firstWAV("../" + wavFileNames_[1], std::fstream::in);
    input_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    if (firstWAV.is_open())
    {
        int counter = 0;
        while (!firstWAV.eof())
        {
            int characterCode = firstWAV.get();
            if (counter < minWAVFileHeaderLength_)
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

void SoundController::returnFinallyOutput()
{
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open("../SoundController/secondStorage.wav", std::fstream::in);
    }
    else
    {
        output_.open("../SoundController/firstStorage.wav", std::fstream::in);
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
    output_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    output_.close();
    output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::trunc);
    output_.close();
}

SoundController::~SoundController()
{
    delete[] bufferOfSamples_;
    delete[] additionalBufferOfSamples_;
    delete[] wavHeader_;
    output_.close();
    input_.close();
}
