#ifndef DILEMMA_PROBABILITY_H
#define DILEMMA_PROBABILITY_H
#include "../GameStrategy.h"

class Probability : public GameStrategy{
private:
        int currentMove_;
        double configParameter_;
        int totalDefectVotes_;
        int totalCooperateVotes_;
public:
    Probability(std::string configDirectory);
    Choice vote() override;
    void update(Choice firstEnemy, Choice secondEnemy) override;
    void restoreStateOfStrategy() override;
    void printStrategyName() override;
    static int convertCharToInt(char value);
    ~Probability() override = default;
};


#endif //DILEMMA_PROBABILITY_H
