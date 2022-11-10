#include "Trivial_Random.h"

TrivialRandom::TrivialRandom(std::string configDirectory)
{
    strategyName_ = "\"TRIVIAL_RANDOM\"";
    configDirectory_ = configDirectory;
}

Choice TrivialRandom::vote()
{
    std::random_device device;
    std::mt19937 range(device());
    std::uniform_int_distribution<std::mt19937::result_type> distance(0, 100);
    return (distance(range) > 50) ? COOPERATE : DEFECT;
}

void TrivialRandom::printStrategyName()
{
    std::cout << strategyName_;
}
