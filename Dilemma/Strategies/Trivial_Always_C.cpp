#include "Trivial_Always_C.h"

TrivialAlwaysC::TrivialAlwaysC()
{
    strategyName_ = "\"TRIVIAL_ALWAYS_C\"";
}

Choice TrivialAlwaysC::vote()
{
    return COOPERATE;
}

void TrivialAlwaysC::printStrategyName()
{
    std::cout << "\"TRIVIAL_ALWAYS_C\"";
}
