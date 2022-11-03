#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>
#include <map>
#include "StrategyFactory.h"
#include "Detailed.h"

enum Modes
{
    detailed = 0,
    fast = 1,
    tournament = 2
};

std::map<std::string, int> modes = {std::make_pair("detailed", 1), std::make_pair("fast", 2), std::make_pair("tournament", 3)};

class GameController {
public:
    GameController(std::string gameMode, std::string matrixFile, std::vector<std::string> names, int steps);
    std::string gameMode_;
    std::string matrixFile_;
    std::vector<std::string> names_;
    int steps_;
    void startGame();
    ~GameController() = default;
};


#endif //DILEMMA_GAMECONTROLLER_H
