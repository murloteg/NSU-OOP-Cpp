#include "GameController.h"

GameController::GameController(std::vector<std::string> strategies, std::string gameMode, int steps, std::string configDirectory, std::string matrixFile)
{
    gameMode_ = std::move(gameMode);
    matrixFile_ = std::move(matrixFile);
    configDirectory_ = std::move(configDirectory);
    strategies_ = std::move(strategies);
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
        vectorWithStrategies_[i] = StrategyFactory::createStrategy(strategies_[i], configDirectory_);
    }
}

void GameController::startGame()
{
    auto currentMode = modes.find(gameMode_);
    switch (currentMode->second)
    {
        case DETAILED:
        {
            prepareStrategies(static_cast<int> (strategies_.size()));
            Detailed detailedMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            detailedMode.play();
            return;
        }

        case FAST:
        {
            prepareStrategies(static_cast<int> (strategies_.size()));
            Fast fastMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            fastMode.play();
            return;
        }

        case TOURNAMENT:
        {
            prepareStrategies(static_cast<int> (strategies_.size()));
            Tournament tournamentMode(steps_, matrixFile_, vectorWithStrategies_);
            tournamentMode.play();
            return;
        }
    }
}

GameController::~GameController()
{
    strategies_.clear();
    vectorWithStrategies_.clear();
}
