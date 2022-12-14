#ifndef DILEMMA_STRATEGYFACTORY_H
#define DILEMMA_STRATEGYFACTORY_H
#include "Trivial_Always_C/Trivial_Always_C.h"
#include "Trivial_Always_D/Trivial_Always_D.h"
#include "Trivial_Random/Trivial_Random.h"
#include "Friendly_Fool/Friendly_Fool.h"
#include "Probability/Probability.h"
#include "Dominator/Dominator.h"
#include <map>
static std::map<std::string, int> availableStrategies {std::make_pair("TRIVIAL_ALWAYS_C", 1), std::make_pair("TRIVIAL_ALWAYS_D", 2),
                                                       std::make_pair("TRIVIAL_RANDOM", 3), std::make_pair("FRIENDLY_FOOL", 4),
                                                       std::make_pair("PROBABILITY", 5), std::make_pair("DOMINATOR", 6)};

class StrategyFactory {
public:
    StrategyFactory() = default;
    static std::shared_ptr<GameStrategy> createStrategy(const std::string& strategyName, const std::string& configDirectory);
};


#endif //DILEMMA_STRATEGYFACTORY_H
