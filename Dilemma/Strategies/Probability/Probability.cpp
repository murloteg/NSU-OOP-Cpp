#include "Probability.h"

Probability::Probability(std::string configDirectory) 
{
    strategyName_ = "\"PROBABILITY\"";
    configDirectory_ = configDirectory;
    std::string filePath = "../ConfigurationFiles/" + configDirectory_ + "/probability.txt";
    configParameter_ = 0;
    std::string stringParameter;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        file >> stringParameter;
    }
    file.close();
    int currentDivider = 10;
    bool isFractionPart = false;
    for (char symbol : stringParameter)
    {
        if ('0' <= symbol && symbol <= '9' || symbol == '.')
        {
            if (symbol == '.' || isFractionPart)
            {
                configParameter_ += (isFractionPart) ? static_cast<double> (convertCharToInt(symbol)) / currentDivider : 0;
                currentDivider *= (isFractionPart) ? 10 : 1;
                isFractionPart = true;
                continue;
            }

            configParameter_ *= 10;
            configParameter_ += convertCharToInt(symbol);
        }
    }
    configParameter_ = (configParameter_ > 100) ? 100 : configParameter_;
    configParameter_ /= 100;
    totalCooperateVotes_ = totalDefectVotes_ = 0;
    currentMove_ = 1;
}

Choice Probability::vote() 
{
    if (currentMove_ == 1 || currentMove_ == 2)
    {
        return COOPERATE;
    }

    double currentProbabilityOfCooperate = static_cast<double> (totalCooperateVotes_) / (totalDefectVotes_ + totalCooperateVotes_);
    double currentProbabilityOfDefect = static_cast<double> (totalDefectVotes_) / (totalDefectVotes_ + totalCooperateVotes_);
    if (currentProbabilityOfCooperate == currentProbabilityOfDefect)
    {
        return DEFECT;
    }

    if (currentProbabilityOfCooperate > configParameter_)
    {
        return COOPERATE;
    }

    else
    {
        return DEFECT;
    }
}

void Probability::update(Choice firstEnemy, Choice secondEnemy) 
{
    if (currentMove_ < 3)
    {
        ++currentMove_;
    }
    totalCooperateVotes_ += (firstEnemy == COOPERATE) ? 1 : 0;
    totalCooperateVotes_ += (secondEnemy == COOPERATE) ? 1 : 0;
    totalDefectVotes_ += (firstEnemy == DEFECT) ? 1 : 0;
    totalDefectVotes_ += (secondEnemy == DEFECT) ? 1 : 0;
}

void Probability::restoreStateOfStrategy() 
{
    totalDefectVotes_ = totalCooperateVotes_ =  0;
    currentMove_ = 1;
}

int Probability::convertCharToInt(char value) 
{
    return (value - '0');
}

void Probability::printStrategyName() 
{
    std::cout << strategyName_;
}
