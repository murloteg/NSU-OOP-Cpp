#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <utility>
#include "StrategyFactory.h"
#include "Detailed/Detailed.h"
#include "Fast/Fast.h"
#include "Tournament/Tournament.h"

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
private:
    std::vector<std::string> strategies_;
    std::string gameMode_;
    int steps_;
    std::string configDirectory_;
    std::string scoreMatrix_;
    std::string matrixOfGameFile_;
    std::vector<std::shared_ptr<GameStrategy>> vectorWithStrategies_;
    std::map<std::string, std::string> scoreMap_;
    static bool isDigit(char symbol);
    static bool isVote(char symbol);
public:
    GameController(std::vector<std::string> strategies, std::string gameMode, int steps, std::string configDirectory, std::string scoreMatrix, std::string matrixFile);
    WorkStatuses createScoreMapByMatrix();
    WorkStatuses checkConfigParameters() const;
    WorkStatuses prepareStrategies(int numberOfStrategies);
    void startGame();
    ~GameController();
};


#endif //DILEMMA_GAMECONTROLLER_H
