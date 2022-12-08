#ifndef SOUND_PROCESSOR_MUTE_H
#define SOUND_PROCESSOR_MUTE_H
#include "Converter.h"

class Mute : public Converter {
private:
    unsigned int startPointSec_;
    unsigned int endPointSec_;
public:
    Mute();
    void mute();
    ~Mute() override = default;
};


#endif //SOUND_PROCESSOR_MUTE_H
