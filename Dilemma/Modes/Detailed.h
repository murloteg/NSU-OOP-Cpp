#ifndef DILEMMA_DETAILED_H
#define DILEMMA_DETAILED_H
#include "GameMode.h"

enum StatusesOfButton
{
    EXIT = 0,
    CONTINUE = 1
};

class Detailed : public GameMode {
private:
    int currentSteps_;
    GameStrategy* firstStrategy_;
    GameStrategy* secondStrategy_;
    GameStrategy* thirdStrategy_;
public:
    StatusesOfButton statusOfButton_;
    Detailed(int steps, std::string matrix, GameStrategy* first, GameStrategy* second, GameStrategy* third);
    void pressButton();
    void viewMatrix() override;
    void updateMatrix(std::string currentScore) override;
    void play() override;
    ~Detailed() override = default;
};


#endif //DILEMMA_DETAILED_H
