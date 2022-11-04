#include "Trivial_Always_C.h"

TrivialAlwaysC::TrivialAlwaysC() {}

Choice TrivialAlwaysC::vote()
{
    return COOPERATE;
}

void TrivialAlwaysC::printStrategyName()
{
    std::cout << "TRIVIAL_ALWAYS_C";
}
