#include "Friendly_Fool.h"

FriendlyFool::FriendlyFool(std::string configDirectory)
{
    strategyName_ = "\"FRIENDLY_FOOL\"";
    configDirectory_ = configDirectory;
    std::string filePath = "../ConfigurationFiles/" + configDirectory_ + "/friendly_fool.txt";
    configParameter_ = 0;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        file >> configParameter_;
    }
    file.close();

    for (int i = 0; i < configParameter_; ++i)
    {
        previousVotes_.push_back(COOPERATE);
    }
}

Choice FriendlyFool::vote()
{
    for (Choice item : previousVotes_)
    {
        if (item == COOPERATE)
        {
            return COOPERATE;
        }
    }
    return DEFECT;
}

void FriendlyFool::shiftVectorOfVotes()
{
    for (int i = 0; i < previousVotes_.size() - 1; ++i)
    {
        previousVotes_[i] = previousVotes_[i + 1];
    }
    previousVotes_[previousVotes_.size() - 1] = DEFECT;
}

void FriendlyFool::update(Choice firstEnemy, Choice secondEnemy)
{
    shiftVectorOfVotes();
    if (firstEnemy == COOPERATE || secondEnemy == COOPERATE)
    {
        previousVotes_[previousVotes_.size() - 1] = COOPERATE;
    }
}

void FriendlyFool::restoreStateOfStrategy()
{
    previousVotes_.clear();
    for (int i = 0; i < configParameter_; ++i)
    {
        previousVotes_.push_back(COOPERATE);
    }
}

void FriendlyFool::printStrategyName()
{
    std::cout << strategyName_;
}

FriendlyFool::~FriendlyFool()
{
    previousVotes_.clear();
}
