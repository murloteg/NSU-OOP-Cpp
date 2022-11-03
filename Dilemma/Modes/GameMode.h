#ifndef DILEMMA_GAMEMODE_H
#define DILEMMA_GAMEMODE_H
#include <string>
#include <fstream>
#include <iostream>

class GameMode {
public:
    int steps_;
    std::string matrix_;
    virtual std::string convertScoreString(std::string scoreString) {};
    virtual void viewMatrix() = 0;
    virtual void updateMatrix(std::string) {};
    virtual ~GameMode() = default;
};

#endif //DILEMMA_GAMEMODE_H
