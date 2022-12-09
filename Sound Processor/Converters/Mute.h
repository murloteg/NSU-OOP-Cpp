#ifndef SOUND_PROCESSOR_MUTE_H
#define SOUND_PROCESSOR_MUTE_H
#include "Converter.h"

class Mute : public Converter {
private:
    // TODO: add something.
public:
    Mute(std::string currentWAV, unsigned int start, unsigned int end);
    void mute();
    ~Mute() override = default;
};


#endif //SOUND_PROCESSOR_MUTE_H
