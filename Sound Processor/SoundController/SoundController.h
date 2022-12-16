#ifndef SOUND_PROCESSOR_SOUNDCONTROLLER_H
#define SOUND_PROCESSOR_SOUNDCONTROLLER_H
#include "ParserWAVHeader.h"
#include "ConfigFile.h"
#include "Converter.h"
#include "ConverterFactory.h"
#include <map>

enum UtilityConsts
{
    DIFFERENCE_UPPER_CASE = 32
};

static std::map<std::string, Converters> converters = {std::make_pair("MUTE", MUTE), std::make_pair("MIX", MIX),
                                                       std::make_pair("RANDOMIZER", RANDOMIZER), std::make_pair("SLOW", SLOW)};

class SoundController {
private:
    std::string firstStoragePath_ = "../SoundController/firstStorage.wav";
    std::string secondStoragePath_ = "../SoundController/secondStorage.wav";
    std::vector<std::string> wavFileNames_;
    size_t currentConverterNumber_;
    size_t convertersNumber_;
    std::shared_ptr<Converter> nextConverter_;
    std::string nextConverterName_;
    ParserWAVHeader parserWav_ = ParserWAVHeader("default");
    ConfigFile configFile_ = ConfigFile("default");
    std::vector<unsigned char> wavHeader_;
    std::vector<unsigned char> bufferOfSamples_;
    std::vector<unsigned char> additionalBufferOfSamples_;
    int currentSecondsInFile_;
    bool isEndOfFile_;
    std::fstream input_;
    std::fstream output_;
    void clearVectors();
    void resetFileFlags();
    void startingPreparations();
    void getNextConverter();
    void getNextBufferData();
    void getNextDataForAdditionalBuffer(int numberOfAdditionalWAV);
    void putHeaderInOutput();
    void putDataInOutput();
    void prepareFinallyOutput();
    static void toUpperCase(std::string& string);
public:
    SoundController(std::vector<std::string> wavFileNames, std::string configFileName);
    void conversion();
    ~SoundController();
};


#endif //SOUND_PROCESSOR_SOUNDCONTROLLER_H
