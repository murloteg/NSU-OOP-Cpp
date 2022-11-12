#ifndef DILEMMA_GAMEMODE_H
#define DILEMMA_GAMEMODE_H
#include "GameStrategy.h"
#include <vector>
#include <map>

class GameMode {
protected:
    int steps_;
    std::string matrix_;
    static int getLengthOfInt(int value);
    static int convertCharToInt(unsigned char symbol);
    static std::string convertScoreString(const std::string& scoreString);
public:
    virtual void printMode() = 0;
    virtual void viewMatrix() = 0;
    virtual void updateMatrix(std::string) = 0;
    virtual void play() = 0;
    virtual ~GameMode() = default;
};

#endif //DILEMMA_GAMEMODE_H
