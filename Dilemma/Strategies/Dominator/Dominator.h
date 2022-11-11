#ifndef DILEMMA_DOMINATOR_H
#define DILEMMA_DOMINATOR_H
#include "../GameStrategy.h"

class Dominator : public GameStrategy {
private:
    int configParameter_;
    int cooperateCounter_;
    bool conditionChecker_;
public:
    Dominator(std::string configDirectory);
    Choice vote() override;
    void update(Choice firstEnemy, Choice secondEnemy) override;
    void restoreStateOfStrategy() override;
    void printStrategyName() override;
    ~Dominator() override = default;
};


#endif //DILEMMA_DOMINATOR_H
