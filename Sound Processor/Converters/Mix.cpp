#include "Mix.h"

Mix::Mix(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

void Mix::getConverterDescription()
{
    std::cout << "This converter mixes two WAV files.\n"
                 "======Configuration Parameters:======\n"
                 "[1]: number of additional WAV file\n"
                 "[2]: certain seconds in first file, where "
                 "the converter starts mixing" << std::endl;
}

void Mix::conversion(unsigned char* firstBuffer, unsigned char* secondBuffer, unsigned int currentSecondsInFile)
{
    if (currentSecondsInFile >= secondParameter_)
    {
        for (int i = 0; i < bufferSize_; ++i)
        {
            firstBuffer[i] = (secondBuffer[i] + firstBuffer[i]) / 2;
        }
    }
}
