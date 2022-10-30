#include "GameController.h"

GameController::GameController(std::string gameMode, std::string matrixFile, std::vector<std::string> names, int steps)
{
    gameMode_ = gameMode;
    matrixFile_ = matrixFile;
    names_ = names;
    steps_ = steps;
}

