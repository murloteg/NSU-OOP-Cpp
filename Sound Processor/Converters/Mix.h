#ifndef SOUND_PROCESSOR_MIX_H
#define SOUND_PROCESSOR_MIX_H
#include "Converter.h"

class Mix : public Converter {
private:

public:
    Mix();
    void mix();
    ~Mix() override = default;
};


#endif //SOUND_PROCESSOR_MIX_H
