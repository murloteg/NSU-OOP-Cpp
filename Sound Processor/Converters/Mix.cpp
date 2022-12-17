#include "Mix.h"

Mix::Mix(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

void Mix::getConverterDescription()
{
    getConverterName();
    std::cout << "This converter mixes two WAV files.\n"
                 "======Configuration Parameters:======\n"
                 "[1]: number of additional WAV file\n"
                 "[2]: start position in WAV file (in sec.)" << std::endl;
    putSeparator();
}

void Mix::conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile)
{
    if (currentSecondsInFile >= secondParameter_)
    {
        for (int i = 0; i < bufferSize_; ++i)
        {
            if (firstBuffer[i] == 0)
            {
                firstBuffer[i] = secondBuffer[i];
                continue;
            }
            firstBuffer[i] = (secondBuffer[i] + firstBuffer[i]) / 2;
        }
    }
}
