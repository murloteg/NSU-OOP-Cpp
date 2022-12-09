#ifndef SOUND_PROCESSOR_CONVERTER_H
#define SOUND_PROCESSOR_CONVERTER_H
#include <iostream>

enum Converters
{
    MUTE = 1,
    MIX = 2,
    MY_NAME_CONV = 3
};

class Converter {
protected:
    unsigned int firstParameter_;
    unsigned int secondParameter_;
    std::string currentWAV_;
public:
    virtual ~Converter() = default;
};


#endif //SOUND_PROCESSOR_CONVERTER_H
