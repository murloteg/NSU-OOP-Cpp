#include "Detailed.h"

Detailed::Detailed(int steps, std::string matrix, std::shared_ptr<GameStrategy> first, std::shared_ptr<GameStrategy> second, std::shared_ptr<GameStrategy> third)
{
    steps_ = steps;
    currentSteps_ = 0;
    matrix_ = std::move(matrix);
    firstStrategy_ = std::move(first);
    secondStrategy_ = std::move(second);
    thirdStrategy_ = std::move(third);
    statusOfButton_ = CONTINUE;
}

void Detailed::printMode()
{
    std::cout << ">>>MODE: DETAILED<<<" << std::endl;
}

void Detailed::viewMatrix()
{
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::ifstream file(matrixPath);
    if (file.is_open())
    {
        firstStrategy_->printStrategyName();
        std::cout << " VS ";
        secondStrategy_->printStrategyName();
        std::cout << " VS ";
        thirdStrategy_->printStrategyName();
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

void Detailed::updateMatrix(std::string currentScore)
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

void Detailed::pressButton()
{
    std::string currentString;
    std::cout << "TYPE \"quit\" to exit. TYPE another string to continue:" << std::endl;
    std::cin >> currentString;
    if (currentString == "quit")
    {
        statusOfButton_ = EXIT;
        return;
    }

    statusOfButton_ = CONTINUE;
    ++currentSteps_;
}

void Detailed::play()
{
    printMode();
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::fstream file(matrixPath, std::ios::out);
    file.close();

    while (true)
    {
        pressButton();
        if (statusOfButton_ == EXIT)
        {
            viewMatrix();
            return;
        }

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
        firstStrategy_->update(secondVote, thirdVote);
        secondStrategy_->update(firstVote, thirdVote);
        thirdStrategy_->update(firstVote, secondVote);
        viewMatrix();
    }
}
