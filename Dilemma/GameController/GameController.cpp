#include "GameController.h"

GameController::GameController(std::vector<std::string> strategies, std::string gameMode, int steps, std::string configDirectory, std::string matrixFile)
{
    gameMode_ = std::move(gameMode);
    matrixFile_ = std::move(matrixFile);
    configDirectory_ = std::move(configDirectory);
    strategies_ = std::move(strategies);
    steps_ = steps;
}

WorkStatuses GameController::checkConfigParameters() const
{
    std::string matrixPath = "../ConfigurationFiles/" + matrixFile_;
    std::string configDirectoryPath = "../ConfigurationFiles/" + configDirectory_;
    std::ifstream matrixFile(matrixPath);
    if (!matrixFile.is_open())
    {
        matrixFile.close();
        return SOMETHING_WENT_WRONG;
    }
    matrixFile.close();

    std::ifstream directoryFile(configDirectoryPath);
    if (!directoryFile.is_open())
    {
        directoryFile.close();
        return SOMETHING_WENT_WRONG;
    }
    directoryFile.close();

    return EVERYTHING_IS_OK;
}

WorkStatuses GameController::prepareStrategies(int numberOfStrategies)
{
    vectorWithStrategies_.clear();
    for (int i = 0; i < numberOfStrategies; ++i)
    {
        vectorWithStrategies_.push_back(nullptr);
    }

    for (int i = 0; i < numberOfStrategies; ++i)
    {
        vectorWithStrategies_[i] = StrategyFactory::createStrategy(strategies_[i], configDirectory_);
        if (vectorWithStrategies_[i] == nullptr)
        {
            return SOMETHING_WENT_WRONG;
        }
    }

    return EVERYTHING_IS_OK;
}

void GameController::startGame()
{
    WorkStatuses statusOfConfigParameters = checkConfigParameters();
    try
    {
        if (statusOfConfigParameters == SOMETHING_WENT_WRONG)
        {
            throw std::invalid_argument("[EXCEPTION]: invalid file path.");
        }
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return;
    }

    WorkStatuses statusOfFactory = prepareStrategies(static_cast<int> (strategies_.size()));
    if (statusOfFactory == SOMETHING_WENT_WRONG)
    {
        return;
    }

    auto currentMode = modes.find(gameMode_);
    switch (currentMode->second)
    {
        case DETAILED:
        {
            Detailed detailedMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            detailedMode.play();
            return;
        }

        case FAST:
        {
            Fast fastMode(steps_, matrixFile_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            fastMode.play();
            return;
        }

        case TOURNAMENT:
        {
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
