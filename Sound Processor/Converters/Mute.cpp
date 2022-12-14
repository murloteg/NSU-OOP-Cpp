#include "Mute.h"

Mute::Mute(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

void Mute::getConverterDescription()
{
    getConverterName();
    std::cout << "This converter mutes interval of seconds from input WAV file.\n"
                 "======Configuration Parameters:======\n"
                 "[1]: start position in WAV file (in sec.)\n"
                 "[2]: end position in WAV file (in sec.)" << std::endl;
    putSeparator();
}

void Mute::conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile)
{
    if (firstParameter_ <= currentSecondsInFile && currentSecondsInFile <= secondParameter_)
    {
        for (int i = 0; i < bufferSize_; ++i)
        {
            firstBuffer[i] = 0;
        }
    }
}
