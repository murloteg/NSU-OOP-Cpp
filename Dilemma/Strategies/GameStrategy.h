#ifndef DILEMMA_GAMESTRATEGY_H
#define DILEMMA_GAMESTRATEGY_H

#endif //DILEMMA_GAMESTRATEGY_H

enum StrategiesNames
{
    TRIVIAL_ALWAYS_C = 1,
    TRIVIAL_ALWAYS_D = 2,
    TRIVIAL_RANDOM = 3
};

enum Choice
{
    COOPERATE = 0,
    DEFECT = 1
};

class GameStrategy {
public:
    virtual Choice vote();
    virtual void update(Choice firstEnemy, Choice secondEnemy);
    virtual ~GameStrategy() = default;
};
