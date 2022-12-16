#ifndef SOUND_PROCESSOR_CONVERTERFACTORY_H
#define SOUND_PROCESSOR_CONVERTERFACTORY_H
#include "Converter.h"
#include "Mute.h"
#include "Mix.h"
#include "Randomizer.h"
#include "SoundController.h"

class ConverterFactory {
private:
    ///
public:
    static std::shared_ptr<Converter> createConverter(std::string nameOfConverter, int bufferSize,
                                      unsigned int firstParameter, unsigned int secondParameter);
};


#endif //SOUND_PROCESSOR_CONVERTERFACTORY_H
