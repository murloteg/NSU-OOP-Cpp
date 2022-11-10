#include "Trivial_Always_C.h"

TrivialAlwaysC::TrivialAlwaysC(std::string configDirectory)
{
    strategyName_ = "\"TRIVIAL_ALWAYS_C\"";
    configDirectory_ = configDirectory;
}

Choice TrivialAlwaysC::vote()
{
    return COOPERATE;
}

void TrivialAlwaysC::printStrategyName()
{
    std::cout << strategyName_;
}
