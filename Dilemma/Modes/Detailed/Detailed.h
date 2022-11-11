#ifndef DILEMMA_DETAILED_H
#define DILEMMA_DETAILED_H
#include "../GameMode.h"

enum StatusesOfButton
{
    EXIT = 0,
    CONTINUE = 1
};

class Detailed : public GameMode {
private:
    int currentSteps_;
    std::shared_ptr<GameStrategy> firstStrategy_;
    std::shared_ptr<GameStrategy> secondStrategy_;
    std::shared_ptr<GameStrategy> thirdStrategy_;
public:
    StatusesOfButton statusOfButton_;
    Detailed(int steps, std::string matrix, std::shared_ptr<GameStrategy> first, std::shared_ptr<GameStrategy> second, std::shared_ptr<GameStrategy> third);
    void pressButton();
    void printMode() override;
    void viewMatrix() override;
    void updateMatrix(std::string currentScore) override;
    void play() override;
    ~Detailed() override = default;
};


#endif //DILEMMA_DETAILED_H
