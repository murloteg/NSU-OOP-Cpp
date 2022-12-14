#include "Slow.h"

Slow::Slow(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

void Slow::getConverterDescription()
{
    getConverterName();
    std::cout << "This converter slow down current WAV file from the specified time interval.\n"
                 "======Configuration Parameters:======\n"
                 "[1]: start position in WAV file (in sec.)\n"
                 "[2]: end position in WAV file (in sec.)" << std::endl;
    putSeparator();
}

void Slow::conversion(std::vector<unsigned char> &firstBuffer, std::vector<unsigned char> &secondBuffer,
                      unsigned int currentSecondsInFile)
{
    if (currentSecondsInFile >= firstParameter_ && currentSecondsInFile <= secondParameter_)
    {
        unsigned int firstBaseSample = 0;
        unsigned int secondBaseSample = 0;
        for (int i = 0; i < bufferSize_ - 1; i += 2)
        {
            if (i % SLOW_PARAMETER == 0)
            {
                firstBaseSample =  firstBuffer[i];
                secondBaseSample =  firstBuffer[i + 1];
            }
            firstBuffer[i] = firstBaseSample;
            firstBuffer[i + 1] = secondBaseSample;
        }
    }
}
