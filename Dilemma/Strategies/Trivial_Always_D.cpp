#include "Trivial_Always_D.h"

TrivialAlwaysD::TrivialAlwaysD() {}

Choice TrivialAlwaysD::vote()
{
    return DEFECT;
}

void TrivialAlwaysD::printStrategyName()
{
    std::cout << "TRIVIAL_ALWAYS_D";
}
