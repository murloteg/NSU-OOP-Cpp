#ifndef SOUND_PROCESSOR_MIX_H
#define SOUND_PROCESSOR_MIX_H
#include "Converter.h"

class Mix : public Converter {
private:

public:
    Mix(unsigned int bufferSize, unsigned int start, unsigned int end);
    unsigned char* mix(unsigned char* buffer, unsigned int currentSecondsInFile); // FIXME
    ~Mix() override = default;
};


#endif //SOUND_PROCESSOR_MIX_H
