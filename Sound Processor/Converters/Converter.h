#ifndef SOUND_PROCESSOR_CONVERTER_H
#define SOUND_PROCESSOR_CONVERTER_H
#include <iostream>
#include <fstream>
#include <vector>

enum Converters
{
    MUTE = 1,
    MIX = 2,
    RANDOMIZER = 3
};

class Converter {
protected:
    unsigned int bufferSize_;
    unsigned int firstParameter_;
    unsigned int secondParameter_;
public:
    virtual ~Converter() = default;
    virtual void conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile) = 0;
    virtual void getConverterDescription() = 0;
};


#endif //SOUND_PROCESSOR_CONVERTER_H
