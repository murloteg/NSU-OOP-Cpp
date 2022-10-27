#ifndef DILEMMA_STRATEGYFACTORY_H
#define DILEMMA_STRATEGYFACTORY_H
#include "Strategies/Trivial_Always_C.h"
#include "Strategies/Trivial_Always_D.h"
#include "Strategies/Trivial_Random.h"
#include <map>

enum StatusesOfFile
{
    UNUSED = 0,
    USED = 1
};

std::map<StatusesOfFile, std::string> configFiles {std::make_pair(UNUSED, "first_strategy.txt"),
                                                   std::make_pair(UNUSED, "second_strategy.txt"),
                                                   std::make_pair(UNUSED, "third_strategy.txt")};

std::map<std::string, int> availableStrategies {std::make_pair("TRIVIAL_ALWAYS_C", 1), std::make_pair("TRIVIAL_ALWAYS_D", 2),
                                                std::make_pair("TRIVIAL_RANDOM", 3)};
// TODO: delete redefinitions of these maps.

class StrategyFactory {
public:
    StrategyFactory() = default;
    static GameStrategy* createStrategy(std::string name);
};


#endif //DILEMMA_STRATEGYFACTORY_H
