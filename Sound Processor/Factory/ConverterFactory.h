#ifndef SOUND_PROCESSOR_CONVERTERFACTORY_H
#define SOUND_PROCESSOR_CONVERTERFACTORY_H
#include "Converter.h"
#include "Mute.h"
#include "Randomizer.h"
#include "SoundController.h"

class ConverterFactory {
public:
    static Converter* createConverter(std::string nameOfConverter, std::string wavFileName, unsigned int firstParameter, unsigned int secondParameter);
};


#endif //SOUND_PROCESSOR_CONVERTERFACTORY_H
