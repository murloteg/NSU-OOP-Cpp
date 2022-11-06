#ifndef DILEMMA_FRIENDLY_FOOL_H
#define DILEMMA_FRIENDLY_FOOL_H
#include "GameStrategy.h"

// TODO: integrate config file.
class FriendlyFool : public GameStrategy {
public:
    std::string configPath; // TODO: add new method.
    FriendlyFool();
    Choice vote() override;
    void update(Choice firstEnemy, Choice secondEnemy) override;
    void printStrategyName() override;
    ~FriendlyFool() override = default;
};


#endif //DILEMMA_FRIENDLY_FOOL_H
