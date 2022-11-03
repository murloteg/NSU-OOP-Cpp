#ifndef DILEMMA_DETAILED_H
#define DILEMMA_DETAILED_H
#include "GameMode.h"
#include "GameStrategy.h"
#include <map>

enum StatusesOfButton
{
    EXIT = 0,
    CONTINUE = 1
};

static std::map<std::string, std::string> scoreTable = {std::make_pair("CCC", "777"), std::make_pair("CCD", "339"),
                                                        std::make_pair("CDC", "393"), std::make_pair("CDD", "055"),
                                                        std::make_pair("DCC", "933"), std::make_pair("DCD", "505"),
                                                        std::make_pair("DDC", "550"), std::make_pair("DDD", "111")};

class Detailed : GameMode {
private:
    int currentSteps_;
    GameStrategy* firstStrategy_;
    GameStrategy* secondStrategy_;
    GameStrategy* thirdStrategy_;
public:
    StatusesOfButton statusOfButton_;
    Detailed(int steps, std::string matrix, GameStrategy* first, GameStrategy* second, GameStrategy* third);
    void pressButton();
    std::string convertScoreString(std::string scoreString) override;
    static int convertCharToInt(unsigned char symbol);
    void viewMatrix() override;
    void updateMatrix(std::string currentScore) override;
    void play();
    ~Detailed() = default;
};


#endif //DILEMMA_DETAILED_H
