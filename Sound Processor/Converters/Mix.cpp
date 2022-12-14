#include "Mix.h"

Mix::Mix(unsigned int bufferSize, unsigned int start, unsigned int end)
{
    bufferSize_ = bufferSize;
    firstParameter_ = start;
    secondParameter_ = end;
}

unsigned char* Mix::mix(unsigned char* buffer, unsigned int currentSecondsInFile)
{

}
