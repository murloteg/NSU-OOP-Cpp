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
    std::vector<std::string> wavFileNames_;
    int minWAVFileHeaderLength_;
    unsigned char* wavHeader_;
    size_t currentConverterNumber_;
    size_t convertersNumber_;
    Converter* nextConverter_;
    std::string nextConverterName_;
    ParserWAV parserWav_ = ParserWAV("default");
    ConfigFile configFile_ = ConfigFile("default");
    unsigned char* bufferOfSamples_; // size = sampleRate.
    unsigned char* additionalBufferOfSamples_;
    int currentSecondsInFile_;
    bool isEndOfFile_;
    std::fstream input_;
    std::fstream output_;
    void getNextConverter();
    void getNextBufferData();
    void getNextDataForAdditionalWAV(int numberOfAdditionalWAV);
    void putHeaderInOutput();
    void putDataInOutput();
    void prepareInputFile();
    void returnFinallyOutput();
    static void toUpperCase(std::string& string);
public:
    SoundController(std::vector<std::string> wavFileNames, std::string configFileName);
    void conversion(); // use converter.
    void debugTest();
    ~SoundController(); // fix later.
};


#endif //SOUND_PROCESSOR_SOUNDCONTROLLER_H
