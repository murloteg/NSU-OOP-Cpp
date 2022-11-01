#include "Trivial_Random.h"

TrivialRandom::TrivialRandom() {}

Choice TrivialRandom::vote()
{
    srand(static_cast<unsigned> (time(nullptr)));
    int randomValue = rand();
    return (randomValue % 2 == 0) ? COOPERATE : DEFECT;
}
