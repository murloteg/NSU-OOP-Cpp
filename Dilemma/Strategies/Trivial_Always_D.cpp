#include "Trivial_Always_D.h"

TrivialAlwaysD::TrivialAlwaysD()
{
    strategyName_ = "\"TRIVIAL_ALWAYS_D\"";
}

Choice TrivialAlwaysD::vote()
{
    return DEFECT;
}

void TrivialAlwaysD::printStrategyName()
{
    std::cout << "\"TRIVIAL_ALWAYS_D\"";
}
