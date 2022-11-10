#ifndef DILEMMA_FAST_H
#define DILEMMA_FAST_H
#include "GameMode.h"

class Fast : public GameMode {
private:
    int currentSteps_;
    std::shared_ptr<GameStrategy> firstStrategy_;
    std::shared_ptr<GameStrategy> secondStrategy_;
    std::shared_ptr<GameStrategy> thirdStrategy_;
public:
    Fast(int steps, std::string matrix, std::shared_ptr<GameStrategy> first, std::shared_ptr<GameStrategy> second, std::shared_ptr<GameStrategy> third);
    void printMode() override;
    void viewMatrix() override;
    void updateMatrix(std::string currentScore) override;
    void play() override;
    ~Fast() override = default;
};


#endif //DILEMMA_FAST_H
