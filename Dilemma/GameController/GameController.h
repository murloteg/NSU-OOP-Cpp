#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>

class GameController {
public:
    std::string gameMode;
    std::string matrixFile;
    std::vector<std::string> names;
    int steps;
};


#endif //DILEMMA_GAMECONTROLLER_H
