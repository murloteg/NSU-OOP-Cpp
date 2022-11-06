#ifndef DILEMMA_FAST_H
#define DILEMMA_FAST_H
#include "GameMode.h"

class Fast : public GameMode {
private:
    int currentSteps_;
    GameStrategy* firstStrategy_;
    GameStrategy* secondStrategy_;
    GameStrategy* thirdStrategy_;
public:
    Fast(int steps, std::string matrix, GameStrategy* first, GameStrategy* second, GameStrategy* third);
    void printMode() override;
    void viewMatrix() override;
    void updateMatrix(std::string currentScore) override;
    void play() override;
    ~Fast() override = default;
};


#endif //DILEMMA_FAST_H
