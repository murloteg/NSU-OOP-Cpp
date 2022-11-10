#ifndef DILEMMA_FRIENDLY_FOOL_H
#define DILEMMA_FRIENDLY_FOOL_H
#include "GameStrategy.h"

class FriendlyFool : public GameStrategy {
private:
    int configParameter_;
    std::vector<Choice> previousVotes_;
public:
    FriendlyFool(std::string configDirectory);
    Choice vote() override;
    void shiftVectorOfVotes();
    void update(Choice firstEnemy, Choice secondEnemy) override;
    void restoreStateOfStrategy() override;
    void printStrategyName() override;
    ~FriendlyFool() override;
};


#endif //DILEMMA_FRIENDLY_FOOL_H
