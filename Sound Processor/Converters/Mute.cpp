#include "Mute.h"

Mute::Mute(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

unsigned char* Mute::mute(unsigned char* buffer, unsigned int currentSecondsInFile)
{
    if (firstParameter_ <= currentSecondsInFile && currentSecondsInFile <= secondParameter_)
    {
        for (int i = 0; i < bufferSize_; ++i)
        {
            buffer[i] = 0;
        }
    }
    return buffer;
}
