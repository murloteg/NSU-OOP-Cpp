#ifndef DILEMMA_STRATEGYFACTORY_H
#define DILEMMA_STRATEGYFACTORY_H
#include "Trivial_Always_C.h"
#include "Trivial_Always_D.h"
#include "Trivial_Random.h"
#include "GameController.h"

class StrategyFactory {
private:
    static GameController gameController;
public:
    StrategyFactory() = default;
    static GameStrategy* createStrategy(std::string name);
};


#endif //DILEMMA_STRATEGYFACTORY_H
