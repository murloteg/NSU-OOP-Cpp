#include "StrategyFactory.h"

GameStrategy *StrategyFactory::createStrategy(std::string name)
{
    auto isAvailableName = availableStrategies.find(name);
    if (isAvailableName == availableStrategies.end())
    {
        throw std::invalid_argument("Unavailable name");
    }

    switch (isAvailableName->second)
    {
        case TRIVIAL_ALWAYS_C:
            return new TrivialAlwaysC();
        case TRIVIAL_ALWAYS_D:
            return new TrivialAlwaysD();
        case TRIVIAL_RANDOM:
            return new TrivialRandom();
        case FRIENDLY_FOOL:
            return new FriendlyFool();
    }
}
