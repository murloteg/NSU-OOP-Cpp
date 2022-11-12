#ifndef DILEMMA_GAMESTRATEGY_H
#define DILEMMA_GAMESTRATEGY_H
#include <iostream>
#include <vector>
#include <fstream>

enum StrategiesNames
{
    TRIVIAL_ALWAYS_C = 1,
    TRIVIAL_ALWAYS_D = 2,
    TRIVIAL_RANDOM = 3,
    FRIENDLY_FOOL = 4,
    PROBABILITY = 5,
    DOMINATOR = 6
};

enum Choice
{
    COOPERATE = 0,
    DEFECT = 1
};

class GameStrategy {
protected:
    std::string configDirectory_;
    std::string strategyName_;
public:
    int strategyScore = 0;
    virtual Choice vote() = 0;
    virtual void update(Choice firstEnemy, Choice secondEnemy) {};
    virtual void restoreStateOfStrategy() {};
    virtual void printStrategyName() = 0;
    std::string getStrategyName() const {return strategyName_;}
    virtual ~GameStrategy() = default;
};

#endif //DILEMMA_GAMESTRATEGY_H
