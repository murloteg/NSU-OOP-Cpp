#ifndef SOUND_PROCESSOR_MUTE_H
#define SOUND_PROCESSOR_MUTE_H
#include "Converter.h"

class Mute : public Converter {
private:
    // TODO: add something.
public:
    Mute(unsigned int bufferSize, unsigned int start, unsigned int end);
    unsigned char* mute(unsigned char* buffer, unsigned int currentSecondsInFile);
    ~Mute() override = default;
};


#endif //SOUND_PROCESSOR_MUTE_H
