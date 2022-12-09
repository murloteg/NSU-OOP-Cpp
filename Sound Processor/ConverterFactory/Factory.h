#ifndef SOUND_PROCESSOR_FACTORY_H
#define SOUND_PROCESSOR_FACTORY_H
#include <map>
#include <iostream>
#include "Converter.h"

// FIXME: add third converter.
std::map<std::string, Converters> converters = {std::make_pair("MUTE", MUTE), std::make_pair("MIX", MIX), std::make_pair("FIX_THIS", MY_NAME_CONV)};

class Factory {
public:
    Factory() = default;
    static Converter& createConverter(std::string name, unsigned int firstParameter, unsigned int secondParameter);
    ~Factory() = default;
};


#endif //SOUND_PROCESSOR_FACTORY_H
