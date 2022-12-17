#ifndef SOUND_PROCESSOR_DESCRIPTION_H
#define SOUND_PROCESSOR_DESCRIPTION_H
#include "Mute.h"
#include "Mix.h"
#include "Randomizer.h"
#include "Slow.h"

enum DescriptionConsts
{
    UNKNOWN = 0
};

class Description {
public:
    Description() = default;
    static void putDescriptions();
    ~Description() = default;
};


#endif //SOUND_PROCESSOR_DESCRIPTION_H
