#include "SoundController.h"

<<<<<<< HEAD
SoundController::SoundController(std::vector<std::string> wavFileNames, std::string configFileName)
=======
SoundController::SoundController(std::ofstream& output, std::vector<std::string> wavFileNames, std::string configFileName) : output_(output)
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
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
<<<<<<< HEAD
    prepareInputFile();
=======
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
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
<<<<<<< HEAD
        if (currentConverterNumber_ > 0)
        {
            putHeaderInOutput();
        }
=======
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
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
<<<<<<< HEAD
                return;
=======
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
                auto converter = dynamic_cast<Randomizer*>(nextConverter_);
//                converter->mute();
                break;
            }

            default:
            {
                break;
            }
        }
<<<<<<< HEAD
        currentSecondsInFile_ = 0;
        isEndOfFile_ = false;
        ++currentConverterNumber_;
    }
    return; ////
    returnFinallyOutput();
=======
        ++currentConverterNumber_;
    }
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
}

void SoundController::getNextConverter()
{
<<<<<<< HEAD
    nextConverterName_ = configFile_.prepareAndConvertParameters();
    toUpperCase(nextConverterName_);
    nextConverter_ = ConverterFactory::createConverter(nextConverterName_, parserWav_.getByteRate(),
                                                       configFile_.getFirstParameter(),
                                                       configFile_.getSecondParameter());
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
        skipUntilCurrentSeconds(input_);
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            if (input_.eof())
=======
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
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
            {
                isEndOfFile_ = true;
                return;
            }
<<<<<<< HEAD
            unsigned char character = input_.get();
            bufferOfSamples_[i] = character;
        }
    }
    input_.close();
}

void SoundController::skipUntilCurrentSeconds(std::fstream& file)
=======
            unsigned char character = input.get();
            bufferOfSamples_[i] = character;
        }
    }
}

void SoundController::skipUntilCurrentSeconds(std::ifstream& file)
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
{
    int counter = 0;
    while (counter < minWAVFileHeaderLength_)
    {
<<<<<<< HEAD
        file.get();
=======
        unsigned char character = file.get();
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
        ++counter;
    }

    counter = 0;
    while (counter < parserWav_.getByteRate() * currentSecondsInFile_)
    {
<<<<<<< HEAD
        file.get();
=======
        unsigned char character = file.get();
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
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
<<<<<<< HEAD
    if (currentConverterNumber_ % 2 == 0)
    {
        input_.open("../SoundController/firstStorage.wav", std::fstream::in);
        output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::trunc);
    }
    else
    {
        input_.open("../SoundController/secondStorage.wav", std::fstream::in);
        output_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    }

    int counter = 0;
=======
    int counter = 0;
    std::ifstream input("../" + wavFileNames_[1]);
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
    if (output_.is_open())
    {
        while (counter < minWAVFileHeaderLength_)
        {
<<<<<<< HEAD
            unsigned char character = input_.get();
=======
            unsigned char character = input.get();
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
            output_ << character;
            ++counter;
        }
    }
<<<<<<< HEAD
    input_.close();
    output_.close();
=======
    input.close();
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
}

void SoundController::putDataInOutput()
{
<<<<<<< HEAD
    if (currentConverterNumber_ % 2 == 0)
    {
        output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::app);
    }
    else
    {
        output_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::app);
    }

=======
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
    if (output_.is_open())
    {
        for (int i = 0; i < parserWav_.getByteRate(); ++i)
        {
            output_ << bufferOfSamples_[i];
        }
    }
<<<<<<< HEAD
    output_.close();
}

void SoundController::prepareInputFile()
{
    std::fstream firstWAV("../" + wavFileNames_[1], std::fstream::in);
    input_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    if (firstWAV.is_open())
    {
        while (!firstWAV.eof())
        {
            unsigned char character = firstWAV.get();
            input_ << character;
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
            unsigned char character = output_.get();
            result << character;
        }
    }
    output_.close();
    result.close();
    input_.open("../SoundController/firstStorage.wav", std::fstream::out | std::fstream::trunc);
    input_.close();
    output_.open("../SoundController/secondStorage.wav", std::fstream::out | std::fstream::trunc);
    output_.close();
}


=======
}

>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
SoundController::~SoundController()
{
    delete[] bufferOfSamples_;
    output_.close();
}
