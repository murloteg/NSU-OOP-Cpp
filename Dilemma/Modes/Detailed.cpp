#include "Detailed.h"

Detailed::Detailed(int steps, std::string matrix, GameStrategy* first, GameStrategy* second, GameStrategy* third)
{
    steps_ = steps;
    currentSteps_ = 0;
    matrix_ = matrix;
    firstStrategy_ = first;
    secondStrategy_ = second;
    thirdStrategy_ = third;
}

std::string Detailed::convertScoreString(std::string scoreString)
{
    std::string result;
    for (char symbol : scoreString)
    {
        result += (symbol == '0') ? "C" : "D";
    }
    return result;
}

int Detailed::convertCharToInt(unsigned char symbol)
{
    return symbol - '0';
}

void Detailed::viewMatrix()
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

void Detailed::updateMatrix(std::string currentScore)
{
    std::string matrixPath = "../ConfigurationFiles/" + matrix_;
    std::ofstream file(matrixPath, std::ios_base::app);
    if (file.is_open())
    {
        if (currentSteps_ == 1)
        {
            file << "P1 P2 P3    S1 S2 S3\n";
        }

        file << currentScore[0] << "  ";
        file << currentScore[1] << "  ";
        file << currentScore[2];
        file << "     ";
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
    if (currentString == "quit" || currentSteps_ == steps_)
    {
        statusOfButton_ = EXIT;
        return;
    }

    statusOfButton_ = CONTINUE;
    ++currentSteps_;
}

void Detailed::play()
{
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
        std::string currentScore = std::to_string(firstVote) + std::to_string(secondVote) + std::to_string(thirdVote);
        currentScore = convertScoreString(currentScore);
        auto scoreString = scoreTable.find(currentScore);
        firstStrategy_->strategyScore += convertCharToInt(scoreString->second[0]);
        secondStrategy_->strategyScore += convertCharToInt(scoreString->second[1]);
        thirdStrategy_->strategyScore += convertCharToInt(scoreString->second[2]);
        updateMatrix(scoreString->first);
        viewMatrix();
    }
}
