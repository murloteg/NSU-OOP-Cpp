#include "StrategyFactory.h"

std::shared_ptr<GameStrategy> StrategyFactory::createStrategy(const std::string& strategyName, const std::string& configDirectory)
{
    auto isAvailableName = availableStrategies.find(strategyName);
    try
    {
        if (isAvailableName == availableStrategies.end())
        {
            throw std::invalid_argument("[EXCEPTION]: unavailable name of strategy: \"");
        }
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << strategyName << "\"" << std::endl;
        return nullptr;
    }

    switch (isAvailableName->second)
    {
        case TRIVIAL_ALWAYS_C:
            return std::shared_ptr<GameStrategy>(new TrivialAlwaysC(configDirectory));
        case TRIVIAL_ALWAYS_D:
            return std::shared_ptr<GameStrategy>(new TrivialAlwaysD(configDirectory));
        case TRIVIAL_RANDOM:
            return std::shared_ptr<GameStrategy>(new TrivialRandom(configDirectory));
        case FRIENDLY_FOOL:
            return std::shared_ptr<GameStrategy>(new FriendlyFool(configDirectory));
        case PROBABILITY:
            return std::shared_ptr<GameStrategy>(new Probability(configDirectory));
        case DOMINATOR:
            return std::shared_ptr<GameStrategy>(new Dominator(configDirectory));
        default:
            return nullptr;
    }
}
