#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>
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

class GameController {
public:
    GameController(std::string gameMode, std::string matrixFile, std::vector<std::string> names, int steps);
    std::string gameMode_;
    std::string matrixFile_;
    std::vector<std::string> names_;
    int steps_;

    ~GameController() = default;
};


#endif //DILEMMA_GAMECONTROLLER_H
