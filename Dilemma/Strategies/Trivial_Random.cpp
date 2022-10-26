#include "Trivial_Random.h"

TrivialRandom::TrivialRandom() {}

Choice TrivialRandom::vote()
{
    unsigned int randomValue = std::rand() / ((RAND_MAX + 1u) / 10);
    if (randomValue >= 5)
    {
        return COOPERATE;
    }

    else
    {
        return DEFECT;
    }
}
