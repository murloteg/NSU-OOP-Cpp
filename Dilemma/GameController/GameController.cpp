#include "GameController.h"

GameController::GameController(std::vector<std::string> strategies, std::string gameMode, int steps, std::string configDirectory, std::string scoreMatrix, std::string matrixFile)
{
    gameMode_ = std::move(gameMode);
    scoreMatrix_ = std::move(scoreMatrix);
    matrixOfGameFile_ = std::move(matrixFile);
    configDirectory_ = std::move(configDirectory);
    strategies_ = std::move(strategies);
    steps_ = steps;
}

WorkStatuses GameController::checkConfigParameters() const
{
    std::string matrixPath = "../ConfigurationFiles/" + matrixOfGameFile_;
    std::string configDirectoryPath = "../ConfigurationFiles/" + configDirectory_;
    std::ifstream matrixFile(matrixPath);
    if (!matrixFile.is_open() || matrixOfGameFile_.empty())
    {
        return SOMETHING_WENT_WRONG;
    }
    matrixFile.close();

    std::ifstream directoryFile(configDirectoryPath);
    if (!directoryFile.is_open() || configDirectory_.empty())
    {
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

bool GameController::isDigit(char symbol)
{
    return ('0' <= symbol && symbol <= '9');
}

bool GameController::isVote(char symbol)
{
    return (symbol == 'C' || symbol == 'D');
}

WorkStatuses GameController::createScoreMapByMatrix()
{
    std::string scoreMatrixPath = "../ConfigurationFiles/" + scoreMatrix_;
    std::ifstream scoreMatrixFile(scoreMatrixPath);
    if (!scoreMatrixFile.is_open() || scoreMatrix_.empty())
    {
        return SOMETHING_WENT_WRONG;
    }

    std::string votesString;
    std::string digitsString;
    char symbol;
    while (!scoreMatrixFile.eof())
    {
        scoreMatrixFile >> symbol;
        if (votesString.size() < 3 && isVote(symbol))
        {
            votesString += symbol;
        }

        else if (votesString.size() == 3 && digitsString.size() < 3 && isDigit(symbol))
        {
            digitsString += symbol;
        }

        if (votesString.size() == 3 && digitsString.size() == 3)
        {
            scoreMap_.insert(std::make_pair(votesString, digitsString));
            votesString.clear();
            digitsString.clear();
        }
    }

    scoreMatrixFile.close();
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

    WorkStatuses mapCreationStatus = createScoreMapByMatrix();
    try
    {
        if (mapCreationStatus == SOMETHING_WENT_WRONG)
        {
            throw std::invalid_argument("[EXCEPTION]: invalid file path.");
        }
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return;
    }

    auto currentMode = modes.find(gameMode_);
    switch (currentMode->second)
    {
        case DETAILED:
        {
            Detailed detailedMode(steps_, matrixOfGameFile_, scoreMap_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            detailedMode.play();
            return;
        }

        case FAST:
        {
            Fast fastMode(steps_, matrixOfGameFile_, scoreMap_, vectorWithStrategies_[0], vectorWithStrategies_[1], vectorWithStrategies_[2]);
            fastMode.play();
            return;
        }

        case TOURNAMENT:
        {
            Tournament tournamentMode(steps_, matrixOfGameFile_, scoreMap_, vectorWithStrategies_);
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
