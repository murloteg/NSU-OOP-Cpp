#ifndef DILEMMA_TRIVIAL_RANDOM_H
#define DILEMMA_TRIVIAL_RANDOM_H
#include "GameStrategy.h"
#include <random>

class TrivialRandom : public GameStrategy{
public:
    TrivialRandom();
    Choice vote() override;
    void printStrategyName() override;
    ~TrivialRandom() override = default;
};


#endif //DILEMMA_TRIVIAL_RANDOM_H
