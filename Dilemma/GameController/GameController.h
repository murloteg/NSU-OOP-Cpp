#ifndef DILEMMA_GAMECONTROLLER_H
#define DILEMMA_GAMECONTROLLER_H
#include <string>
#include <vector>

class GameController {
public:
    GameController(std::string gameMode, std::string matrixFile, std::vector<std::string> names, int steps);
    std::string gameMode_;
    std::string matrixFile_;
    std::vector<std::string> names_;
    int steps_;

    ~GameController() = default;
};


#endif //DILEMMA_GAMECONTROLLER_H
