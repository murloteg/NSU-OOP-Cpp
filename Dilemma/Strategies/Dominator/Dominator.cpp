#include "Dominator.h"

Dominator::Dominator(std::string configDirectory)
{
    strategyName_ = "\"DOMINATOR\"";
    configDirectory_ = configDirectory;
    std::string filePath = "../ConfigurationFiles/" + configDirectory_ + "/dominator.txt";
    configParameter_ = 0;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        file >> configParameter_;
    }
    file.close();
    cooperateCounter_ = 0;
    conditionChecker_ = true;
}

Choice Dominator::vote()
{
    if (!conditionChecker_ || cooperateCounter_ == configParameter_)
    {
        cooperateCounter_ %= configParameter_;
        return DEFECT;
    }

    ++cooperateCounter_;
    return COOPERATE;
}

void Dominator::update(Choice firstEnemy, Choice secondEnemy)
{
    conditionChecker_ = !(firstEnemy == DEFECT || secondEnemy == DEFECT) && (conditionChecker_);
}

void Dominator::restoreStateOfStrategy()
{
    cooperateCounter_ = 0;
    conditionChecker_ = true;
}

void Dominator::printStrategyName()
{
    std::cout << strategyName_;
}
