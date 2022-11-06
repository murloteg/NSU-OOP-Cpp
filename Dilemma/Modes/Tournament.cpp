#include "Tournament.h"

Tournament::Tournament(int steps, std::string matrix, std::vector<GameStrategy*> arrayWithStrategies)
{
    steps_ = steps;
    currentSteps_ = 0;
    currentRound_ = 0;
    matrix_ = matrix;
    for (int i = 0; i < arrayWithStrategies.size(); ++i)
    {
        scoresOfStrategies_.push_back(0);
    }
    vectorWithStrategies_ = std::move(arrayWithStrategies);
    currentFirstIndex = currentSecondIndex = currentThirdIndex = 0;
}

void Tournament::printMode()
{
    std::cout << ">>>MODE: TOURNAMENT<<<" << std::endl;
}

void Tournament::printCurrentRound() const
{
    std::cout << "ROUND " << currentRound_ << ":" << std::endl;
}


void Tournament::viewMatrix()
{
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::ifstream file(matrixPath);
    if (file.is_open())
    {
        vectorWithStrategies_[currentFirstIndex]->printStrategyName();
        std::cout << " VS ";
        vectorWithStrategies_[currentSecondIndex]->printStrategyName();
        std::cout << " VS ";
        vectorWithStrategies_[currentThirdIndex]->printStrategyName();
        std::cout << std::endl;

        while (!file.eof())
        {
            char currentChar = static_cast<char> (file.get());
            if (currentChar != EOF)
            {
                std::cout << currentChar;
            }

            else
            {
                break;
            }
        }
    }

    std::cout << std::endl;
    file.close();
}

void Tournament::viewFinalProtocol()
{
    std::cout << "=======[FINAL PROTOCOL]========" << std::endl;
    std::multimap<std::string, int> results;
    for (int i = 0; i < vectorWithStrategies_.size(); ++i)
    {
        results.insert(std::make_pair(vectorWithStrategies_[i]->getStrategyName(), scoresOfStrategies_[i]));
    }

    for (const auto& item : results)
    {
        std::cout << item.first << " : " << item.second << std::endl;
    }
    std::cout << std::endl;
}

void Tournament::viewWinner()
{
    int maxScore = 0;
    GameStrategy* winner = nullptr;
    for (int i = 0; i < scoresOfStrategies_.size(); ++i)
    {
        if (scoresOfStrategies_[i] > maxScore)
        {
            maxScore = scoresOfStrategies_[i];
            winner = vectorWithStrategies_[i];
        }
    }

    std::cout << "!!! WINNER IS: ";
    winner->printStrategyName();
    std::cout << " !!! " << std::endl;
}

void Tournament::updateMatrix(std::string currentScore)
{
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::ofstream file(matrixPath, std::ios_base::app);
    if (file.is_open())
    {
        if (currentSteps_ == 1)
        {
            file << "=========[THE MATRIX]==========\n";
            file << "P1 P2 P3              S1 S2 S3\n";
        }

        file << currentScore[0] << "  ";
        file << currentScore[1] << "  ";
        file << currentScore[2];
        if (getLengthOfInt(currentSteps_) < 2)
        {
            file << "    ==["  << currentSteps_ << "]==    ";
        }

        else
        {
            file << "    ==["  << currentSteps_ << "]==   ";
        }
        file << vectorWithStrategies_[currentFirstIndex]->strategyScore << "  ";
        file << vectorWithStrategies_[currentSecondIndex]->strategyScore << "  ";
        file << vectorWithStrategies_[currentThirdIndex]->strategyScore << std::endl;
    }
    file.close();
}

void Tournament::play()
{
    printMode();
    for (int i = 0; i < vectorWithStrategies_.size(); ++i)
    {
        for (int j = i + 1; j < vectorWithStrategies_.size(); ++j)
        {
            for (int k = j + 1; k < vectorWithStrategies_.size(); ++k)
            {
                ++currentRound_;
                printCurrentRound();
                GameStrategy* first = vectorWithStrategies_[i];
                GameStrategy* second = vectorWithStrategies_[j];
                GameStrategy* third = vectorWithStrategies_[k];
                currentFirstIndex = i;
                currentSecondIndex = j;
                currentThirdIndex = k;
                std::string matrixPath = "../ConfigurationFiles/" + matrix_;
                std::fstream file(matrixPath, std::ios::out);
                file.close();

                while (currentSteps_ < steps_)
                {
                    ++currentSteps_;
                    Choice firstVote = first->vote();
                    Choice secondVote = second->vote();
                    Choice thirdVote = third->vote();
                    std::string currentVotes = std::to_string(firstVote) + std::to_string(secondVote) + std::to_string(thirdVote);
                    currentVotes = convertScoreString(currentVotes);
                    auto scoreString = scoreTable.find(currentVotes);
                    first->strategyScore += convertCharToInt(scoreString->second[0]);
                    second->strategyScore += convertCharToInt(scoreString->second[1]);
                    third->strategyScore += convertCharToInt(scoreString->second[2]);
                    updateMatrix(scoreString->first);
                }
                scoresOfStrategies_[i] += first->strategyScore;
                scoresOfStrategies_[j] += second->strategyScore;
                scoresOfStrategies_[k] += third->strategyScore;
                currentSteps_ = 0;
                first->strategyScore = 0;
                second->strategyScore = 0;
                third->strategyScore = 0;
                viewMatrix();
            }
        }
    }
    viewFinalProtocol();
    viewWinner();
}
