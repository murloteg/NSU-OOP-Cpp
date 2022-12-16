#ifndef SOUND_PROCESSOR_MUTE_H
#define SOUND_PROCESSOR_MUTE_H
#include "Converter.h"

class Mute : public Converter {
private:
    // TODO: add something.
public:
    Mute(unsigned int bufferSize, unsigned int start, unsigned int end);
    void getConverterDescription() override;
    void conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile) override;
    ~Mute() override = default;
};


#endif //SOUND_PROCESSOR_MUTE_H
