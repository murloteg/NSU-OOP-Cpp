#include "SoundController.h"

SoundController::SoundController(std::ofstream& output, std::vector<std::string> wavFileNames, std::string configFileName) : output_(output)
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
    getNextBufferData();
    nextConverter_ = nullptr;
    putHeaderInOutput();
}

void SoundController::debugTest()
{
    this->parserWav_.debugPrintWAV();
//    this->configFile_.debugPrint();
    std::string converter = configFile_.prepareAndConvertParameters();
    unsigned int firstParam = configFile_.getFirstParameter();
    unsigned int sec = configFile_.getSecondParameter();
    std::cout << converter << " " << firstParam << " " << sec << std::endl;
    converter = configFile_.prepareAndConvertParameters();
    firstParam = configFile_.getFirstParameter();
    sec = configFile_.getSecondParameter();
    std::cout << converter << " " << firstParam << " " << sec << std::endl;
}

void SoundController::conversion()
{
    while (currentConverterNumber_ < convertersNumber_)
    {
        getNextConverter();
        auto converterName = converters.find(nextConverterName_);
        switch (converterName->second)
        {
            case MUTE:
            {
                while (!isEndOfFile_)
                {
                    auto converter = dynamic_cast<Mute*>(nextConverter_);
                    bufferOfSamples_ = converter->mute(bufferOfSamples_, currentSecondsInFile_);
                    putDataInOutput();
                    getNextBufferData();
                    ++currentSecondsInFile_;
                }
                configFile_.increaseCurrentCommandIndex_();
                break;
            }

            case MIX:
            {
                auto converter = dynamic_cast<Mix*>(nextConverter_);
//                converter->mute();
                break;
            }

            case MY_NAME_CONV: // FIXME later.
            {
                auto converter = dynamic_cast<Randomizer*>(nextConverter_);
//                converter->mute();
                break;
            }

            default:
            {
                break;
            }
        }
        ++currentConverterNumber_;
    }
}

void SoundController::getNextConverter()
{
    if (currentConverterNumber_ == 0)
    {
        nextConverterName_ = configFile_.prepareAndConvertParameters();
        toUpperCase(nextConverterName_);
        nextConverter_ = ConverterFactory::createConverter(nextConverterName_, parserWav_.getByteRate(),
                                                           configFile_.getFirstParameter(),
                                                           configFile_.getSecondParameter());

    }

    else
    {
        nextConverterName_ = configFile_.prepareAndConvertParameters();
        nextConverter_ = ConverterFactory::createConverter(nextConverterName_, parserWav_.getByteRate(),
                                                           configFile_.getFirstParameter(),
                                                           configFile_.getSecondParameter());
    }
}

void SoundController::getNextBufferData()
{
    std::ifstream input("../" + wavFileNames_[currentConverterNumber_ + 1]);
    if (input.is_open())
    {
        skipUntilCurrentSeconds(input);
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            if (input.eof())
            {
                isEndOfFile_ = true;
                return;
            }
            unsigned char character = input.get();
            bufferOfSamples_[i] = character;
        }
    }
}

void SoundController::skipUntilCurrentSeconds(std::ifstream& file)
{
    int counter = 0;
    while (counter < minWAVFileHeaderLength_)
    {
        unsigned char character = file.get();
        ++counter;
    }

    counter = 0;
    while (counter < parserWav_.getByteRate() * currentSecondsInFile_)
    {
        unsigned char character = file.get();
        ++counter;
    }
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
    int counter = 0;
    std::ifstream input("../" + wavFileNames_[1]);
    if (output_.is_open())
    {
        while (counter < minWAVFileHeaderLength_)
        {
            unsigned char character = input.get();
            output_ << character;
            ++counter;
        }
    }
    input.close();
}

void SoundController::putDataInOutput()
{
    if (output_.is_open())
    {
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            output_ << bufferOfSamples_[i];
        }
    }
}

SoundController::~SoundController()
{
    delete[] bufferOfSamples_;
    output_.close();
}
