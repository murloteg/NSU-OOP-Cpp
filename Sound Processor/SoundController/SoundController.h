#ifndef SOUND_PROCESSOR_SOUNDCONTROLLER_H
#define SOUND_PROCESSOR_SOUNDCONTROLLER_H
#include "ParserWAV.h"
#include "ConfigFile.h"
#include "Converter.h"
#include "ConverterFactory.h"
#include <map>

static std::map<std::string, Converters> converters = {std::make_pair("MUTE", MUTE), std::make_pair("MIX", MIX), std::make_pair("FIX_THIS", MY_NAME_CONV)};

class SoundController {
private:
    std::string configFileName_;
    std::string wavFileName_;
    ParserWAV parserWav_ = ParserWAV(wavFileName_);
    ConfigFile configFile_ = ConfigFile(configFileName_);
    std::vector<int> bufferOfSamples_; // size = sampleRate.
public:
    SoundController(std::string wavFileName, std::string configFileName);
    void conversion(); // use converter.
    void debugTest();
    ~SoundController() = default; // fix later.
};


#endif //SOUND_PROCESSOR_SOUNDCONTROLLER_H
