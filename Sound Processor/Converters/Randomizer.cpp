#include "Randomizer.h"

Randomizer::Randomizer(std::string currentWAV, unsigned int start, unsigned int end)
{
    firstParameter_ = start;
    secondParameter_ = end;
    currentWAV_ = currentWAV;
}
