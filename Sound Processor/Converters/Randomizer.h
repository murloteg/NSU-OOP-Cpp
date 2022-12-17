#ifndef SOUND_PROCESSOR_RANDOMIZER_H
#define SOUND_PROCESSOR_RANDOMIZER_H
#include "Converter.h"
#include <random>

class Randomizer : public Converter {
private:
    int changedSamples_;
    static unsigned char getRandomChar();
    void getConverterName() override {std::cout << "RANDOMIZER:" << std::endl;}
public:
    Randomizer(unsigned int bufferSize, unsigned int start, unsigned int numberOfSamples);
    void getConverterDescription() override;
    void conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile) override;
    ~Randomizer() override = default;
};

#endif //SOUND_PROCESSOR_RANDOMIZER_H
