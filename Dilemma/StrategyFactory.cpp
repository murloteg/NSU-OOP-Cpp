#include "StrategyFactory.h"

GameStrategy *StrategyFactory::createStrategy(std::string name)
{
    auto isAvailableName = availableStrategies.find(name);
    if (isAvailableName == availableStrategies.end())
    {
        throw std::invalid_argument("Unavailable name");
    }

    auto unusedFile = configFiles.find(UNUSED);
    switch (isAvailableName->second)
    {
        case TRIVIAL_ALWAYS_C:
        {
            configFiles.extract(UNUSED);
            configFiles.insert(std::make_pair(USED, unusedFile->second));
            return new TrivialAlwaysC();
        }

        case TRIVIAL_ALWAYS_D:
        {
            configFiles.extract(UNUSED);
            configFiles.insert(std::make_pair(USED, unusedFile->second));
            return new TrivialAlwaysD();
        }

        case TRIVIAL_RANDOM:
        {
            configFiles.extract(UNUSED);
            configFiles.insert(std::make_pair(USED, unusedFile->second));
            return new TrivialRandom();
        }
    }
}
