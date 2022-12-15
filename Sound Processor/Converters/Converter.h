#ifndef SOUND_PROCESSOR_CONVERTER_H
#define SOUND_PROCESSOR_CONVERTER_H
#include <iostream>
#include <fstream>

enum Converters
{
    MUTE = 1,
    MIX = 2,
    MY_NAME_CONV = 3 // FIXME
};

class Converter {
protected:
    unsigned int bufferSize_;
    unsigned int firstParameter_;
    unsigned int secondParameter_;
public:
    virtual ~Converter() = default;
    virtual void conversion(unsigned char* firstBuffer, unsigned char* secondBuffer, unsigned int currentSecondsInFile) = 0;
    virtual void getConverterDescription() = 0;
};


#endif //SOUND_PROCESSOR_CONVERTER_H
