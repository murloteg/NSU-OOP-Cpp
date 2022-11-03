#include "GameController.h"

GameController::GameController(std::string gameMode, std::string matrixFile, std::vector<std::string> names, int steps)
{
    gameMode_ = gameMode;
    matrixFile_ = matrixFile;
    names_ = names;
    steps_ = steps;
}

void GameController::startGame()
{
    auto* firstStrategy = StrategyFactory::createStrategy(names_[0]);
    auto* secondStrategy = StrategyFactory::createStrategy(names_[1]);
    auto* thirdStrategy = StrategyFactory::createStrategy(names_[2]);
    auto currentMode = modes.find(gameMode_);
    switch (currentMode->second)
    {
        case detailed:
        {
            Detailed detailedMode(steps_, matrixFile_, firstStrategy, secondStrategy, thirdStrategy);
            detailedMode.play();
        }

        case fast:
        {

        }

        case tournament:
        {

        }
    }
}
