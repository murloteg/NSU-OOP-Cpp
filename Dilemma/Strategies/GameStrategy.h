#ifndef DILEMMA_GAMESTRATEGY_H
#define DILEMMA_GAMESTRATEGY_H
#include <iostream>

enum StrategiesNames
{
    TRIVIAL_ALWAYS_C = 1,
    TRIVIAL_ALWAYS_D = 2,
    TRIVIAL_RANDOM = 3,
    FRIENDLY_FOOL = 4,
    PROBABILITY = 5, // Probability-Is-Power
    DOMINATOR = 6 // D-MEANS-DOMINATOR
};

enum Choice
{
    COOPERATE = 0,
    DEFECT = 1
};

class GameStrategy {
public:
    virtual Choice vote() = 0;
    virtual void update(Choice firstEnemy, Choice secondEnemy) {};
    virtual ~GameStrategy() = default;
};

#endif //DILEMMA_GAMESTRATEGY_H
