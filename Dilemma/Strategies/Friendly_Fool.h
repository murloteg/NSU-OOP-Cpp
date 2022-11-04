#ifndef DILEMMA_FRIENDLY_FOOL_H
#define DILEMMA_FRIENDLY_FOOL_H
#include "GameStrategy.h"

class FriendlyFool : public GameStrategy {
public:
    std::string configPath;
    FriendlyFool();
    Choice vote() override;
    void update(Choice firstEnemy, Choice secondEnemy) override;
    void printStrategyName() override;
    ~FriendlyFool() override = default;
};


#endif //DILEMMA_FRIENDLY_FOOL_H
