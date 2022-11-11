#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>
#include <map>
#include "StrategyFactory.h"
#include "Detailed.h"
#include "Fast.h"
#include "Tournament.h"

enum Modes
{
    DETAILED = 1,
    FAST = 2,
    TOURNAMENT = 3
};

enum WorkStatuses
{
    SOMETHING_WENT_WRONG = 0,
    EVERYTHING_IS_OK = 1
};

static std::map<std::string, int> modes = {std::make_pair("DETAILED", 1), std::make_pair("FAST", 2), std::make_pair("TOURNAMENT", 3)};

class GameController {
public:
    GameController(std::vector<std::string> strategies, std::string gameMode, int steps, std::string configDirectory, std::string matrixFile);
    std::string gameMode_;
    std::string matrixFile_;
    std::string configDirectory_;
    std::vector<std::string> strategies_;
    int steps_;
    std::vector<std::shared_ptr<GameStrategy>> vectorWithStrategies_;
    WorkStatuses checkConfigParameters() const;
    WorkStatuses prepareStrategies(int numberOfStrategies);
    void startGame();
    ~GameController();
};


#endif //DILEMMA_GAMECONTROLLER_H
