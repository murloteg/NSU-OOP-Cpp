#include "Randomizer.h"

Randomizer::Randomizer(unsigned int bufferSize, unsigned int start, unsigned int numberOfSamples)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = numberOfSamples;
    changedSamples_ = 0;
}

void Randomizer::getConverterDescription()
{
    std::cout << "This converter randomly change specified number of samples starting from certain position in WAV file.\n"
                 "======Configuration Parameters:======\n"
                 "[1]: start position in WAV file (in sec.)\n"
                 "[2]: number of samples to be changed" << std::endl;
}

unsigned char Randomizer::getRandomChar()
{
    std::random_device device;
    std::mt19937 range(device());
    std::uniform_int_distribution<std::mt19937::result_type> distance(0, 255);
    return distance(range);
}

void Randomizer::conversion(std::vector<unsigned char> &firstBuffer, std::vector<unsigned char> &secondBuffer,
                            unsigned int currentSecondsInFile)
{
    std::random_device device;
    std::mt19937 localRange(device());
    std::uniform_int_distribution<std::mt19937::result_type> distance(1, 2);
    if (currentSecondsInFile >= firstParameter_ && changedSamples_ < secondParameter_)
    {
        unsigned int currentRandomValue = distance(localRange);
        if (currentRandomValue % 2 == 0)
        {
            unsigned char randomCharacter = getRandomChar();
            for (int i = 0; i < bufferSize_; ++i)
            {
                firstBuffer[i] = randomCharacter;
                randomCharacter  = (randomCharacter + 1) % 255;
            }
            ++changedSamples_;
        }

        else
        {
            return;
        }
    }
}
