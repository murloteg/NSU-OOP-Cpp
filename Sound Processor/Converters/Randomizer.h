#ifndef SOUND_PROCESSOR_RANDOMIZATOR_H
#define SOUND_PROCESSOR_RANDOMIZATOR_H
#include "Converter.h"

/* Changing certain number of samples (random values) */
class Randomizer : public Converter{
private:
    int numberOfSamples_;
public:
    Randomizer(std::string currentWAV, unsigned int start, unsigned int end);
};

#endif //SOUND_PROCESSOR_RANDOMIZATOR_H