#include "Trivial_Always_D.h"

TrivialAlwaysD::TrivialAlwaysD(std::string configDirectory)
{
    strategyName_ = "\"TRIVIAL_ALWAYS_D\"";
    configDirectory_ = configDirectory;
}

Choice TrivialAlwaysD::vote()
{
    return DEFECT;
}

void TrivialAlwaysD::printStrategyName()
{
    std::cout << strategyName_;
}
