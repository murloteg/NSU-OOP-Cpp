#include "Description.h"

void Description::putDescriptions()
{
    std::cout << "=====[DESCRIPTION OF CONVERTERS]=====" << std::endl;
    Mute(UNKNOWN, UNKNOWN, UNKNOWN).getConverterDescription();
    Mix(UNKNOWN, UNKNOWN, UNKNOWN).getConverterDescription();
    Randomizer(UNKNOWN, UNKNOWN, UNKNOWN).getConverterDescription();
    Slow(UNKNOWN, UNKNOWN, UNKNOWN).getConverterDescription();
}
