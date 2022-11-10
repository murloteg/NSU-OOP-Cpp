#include "GameController.h"

GameController::GameController(std::string gameMode, std::string matrixFile, std::string configDirectory, std::vector<std::string> names, int steps)
{
    gameMode_ = gameMode;
    matrixFile_ = matrixFile;
    configDirectory_ = configDirectory;
    names_ = names;
    steps_ = steps;
}

void GameController::prepareStrategies(int numberOfStrategies)
{
    vectorWithStrategies_.clear();
    for (int i = 0; i < numberOfStrategies; ++i)
    {
        vectorWithStrategies_.push_back(nullptr);
    }

    for (int i = 0; i < numberOfStrategies; ++i)
    {
        vectorWithStrategies_[i] = StrategyFactory::createStrategy(names_[i], configDirectory_);
    }
}

void GameController::startGame()
{
    auto currentMode = modes.find(gameMode_);
    switch (currentMode->second)
    {
        case detailed:
        {
            prepareStrategies(static_cast<int> (names_.size()));
            Detailed detailedMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            detailedMode.play();
        }

        case fast:
        {
            prepareStrategies(static_cast<int> (names_.size()));
            Fast fastMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            fastMode.play();
        }

        case tournament:
        {
            prepareStrategies(static_cast<int> (names_.size()));
            Tournament tournamentMode(steps_, matrixFile_, vectorWithStrategies_);
            tournamentMode.play();
        }
    }
}
