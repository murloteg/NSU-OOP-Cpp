#ifndef SOUND_PROCESSOR_CONVERTER_H
#define SOUND_PROCESSOR_CONVERTER_H
#include <iostream>

class Converter {
private:
    std::string firstWAV_;
public:
    virtual ~Converter() = default;
};


#endif //SOUND_PROCESSOR_CONVERTER_H
