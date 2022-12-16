#ifndef SOUND_PROCESSOR_MIX_H
#define SOUND_PROCESSOR_MIX_H
#include "Converter.h"

class Mix : public Converter {
private:

public:
    Mix(unsigned int bufferSize, unsigned int start, unsigned int end);
    void getConverterDescription() override;
    void conversion(std::vector<unsigned char>& firstBuffer, std::vector<unsigned char>& secondBuffer, unsigned int currentSecondsInFile) override;
    ~Mix() override = default;
};


#endif //SOUND_PROCESSOR_MIX_H
