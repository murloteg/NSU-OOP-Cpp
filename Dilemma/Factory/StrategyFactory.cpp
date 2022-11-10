#include "StrategyFactory.h"

GameStrategy *StrategyFactory::createStrategy(std::string strategyName, const std::string& configDirectory)
{
    auto isAvailableName = availableStrategies.find(strategyName);
    if (isAvailableName == availableStrategies.end())
    {
        throw std::invalid_argument("Unavailable name");
    }

    switch (isAvailableName->second)
    {
        case TRIVIAL_ALWAYS_C:
            return new TrivialAlwaysC(configDirectory);
        case TRIVIAL_ALWAYS_D:
            return new TrivialAlwaysD(configDirectory);
        case TRIVIAL_RANDOM:
            return new TrivialRandom(configDirectory);
        case FRIENDLY_FOOL:
            return new FriendlyFool(configDirectory);
        case PROBABILITY:
            return new Probability(configDirectory);
        case DOMINATOR:
            return new Dominator(configDirectory);
    }
}
