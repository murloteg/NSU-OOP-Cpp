#include "Fast.h"

Fast::Fast(int steps, std::string matrix, GameStrategy *first, GameStrategy *second, GameStrategy *third)
{
    currentSteps_ = 0;
    steps_ = steps;
    matrix_ = matrix;
    firstStrategy_ = first;
    secondStrategy_ = second;
    thirdStrategy_ = third;
}

void Fast::printMode()
{
    std::cout << ">>>MODE: FAST<<<" << std::endl;
}

void Fast::viewMatrix()
{
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::ifstream file(matrixPath);
    if (file.is_open())
    {
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

void Fast::updateMatrix(std::string currentScore)
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
        file << firstStrategy_->strategyScore << "  ";
        file << secondStrategy_->strategyScore << "  ";
        file << thirdStrategy_->strategyScore << std::endl;
    }
    file.close();
}

void Fast::play()
{
    printMode();
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::fstream file(matrixPath, std::ios::out);
    file.close();

    while (currentSteps_ < steps_)
    {
        ++currentSteps_;
        Choice firstVote = firstStrategy_->vote();
        Choice secondVote = secondStrategy_->vote();
        Choice thirdVote = thirdStrategy_->vote();
        std::string currentVotes = std::to_string(firstVote) + std::to_string(secondVote) + std::to_string(thirdVote);
        currentVotes = convertScoreString(currentVotes);
        auto scoreString = scoreTable.find(currentVotes);
        firstStrategy_->strategyScore += convertCharToInt(scoreString->second[0]);
        secondStrategy_->strategyScore += convertCharToInt(scoreString->second[1]);
        thirdStrategy_->strategyScore += convertCharToInt(scoreString->second[2]);
        updateMatrix(scoreString->first);
    }
    viewMatrix();
}
