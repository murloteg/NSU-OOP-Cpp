#ifndef SOUND_PROCESSOR_SLOWCONVERTER_H
#define SOUND_PROCESSOR_SLOWCONVERTER_H
#include "Converter.h"

enum SlowConsts
{
    SLOW_PARAMETER = 45
};

class Slow : public Converter {
private:

public:
    Slow(unsigned int bufferSize, unsigned int start, unsigned int end);
    void getConverterDescription() override;
    void conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile) override;
    ~Slow() override = default;
};


#endif //SOUND_PROCESSOR_SLOWCONVERTER_H
