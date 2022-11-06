#ifndef DILEMMA_GAMEMODE_H
#define DILEMMA_GAMEMODE_H
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "GameStrategy.h"

class GameMode {
public:
    int steps_;
    std::string matrix_;
    static int getLengthOfInt(int value);
    static std::string convertScoreString(std::string scoreString);
    static int convertCharToInt(unsigned char symbol);
    virtual void printMode() = 0;
    virtual void viewMatrix() = 0;
    virtual void updateMatrix(std::string) = 0;
    virtual void play() = 0;
    virtual ~GameMode() = default;
    std::map<std::string, std::string> scoreTable = {std::make_pair("CCC", "777"), std::make_pair("CCD", "339"),
                                                     std::make_pair("CDC", "393"), std::make_pair("CDD", "055"),
                                                     std::make_pair("DCC", "933"), std::make_pair("DCD", "505"),
                                                     std::make_pair("DDC", "550"), std::make_pair("DDD", "111")};
};

#endif //DILEMMA_GAMEMODE_H
