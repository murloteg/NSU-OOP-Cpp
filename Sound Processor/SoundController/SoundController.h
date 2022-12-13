#ifndef SOUND_PROCESSOR_SOUNDCONTROLLER_H
#define SOUND_PROCESSOR_SOUNDCONTROLLER_H
#include "ParserWAV.h"
#include "ConfigFile.h"
#include "Converter.h"
#include "ConverterFactory.h"
#include <map>

enum FileConsts
{
    FIRST = 1,
    SECOND = 0
};

static std::map<std::string, Converters> converters = {std::make_pair("MUTE", MUTE), std::make_pair("MIX", MIX), std::make_pair("FIX_THIS", MY_NAME_CONV)};

class SoundController {
private:
    std::string configFileName_;
    std::vector<std::string> wavFileNames_;
    int minWAVFileHeaderLength_;
    size_t currentConverterNumber_;
    size_t convertersNumber_;
    Converter* nextConverter_;
    std::string nextConverterName_;
    ParserWAV parserWav_ = ParserWAV("default");
    ConfigFile configFile_ = ConfigFile("default");
    unsigned char* bufferOfSamples_; // size = sampleRate.
    int currentSecondsInFile_;
    bool isEndOfFile_;
<<<<<<< HEAD
    std::fstream input_;
    std::fstream output_;
=======
    std::ofstream& output_;
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
    void getNextConverter();
    void getNextBufferData();
    void putHeaderInOutput();
    void putDataInOutput();
<<<<<<< HEAD
    void skipUntilCurrentSeconds(std::fstream& file);
    void prepareInputFile();
    void returnFinallyOutput();
    static void toUpperCase(std::string& string);
public:
    SoundController(std::vector<std::string> wavFileNames, std::string configFileName);
=======
    void skipUntilCurrentSeconds(std::ifstream& file);
    static void toUpperCase(std::string& string);
public:
    SoundController(std::ofstream& output, std::vector<std::string> wavFileNames, std::string configFileName);
>>>>>>> 99c0a896c270a6b61e1ab0f8d00b4ea4bb246e65
    void conversion(); // use converter.
    void debugTest();
    ~SoundController(); // fix later.
};


#endif //SOUND_PROCESSOR_SOUNDCONTROLLER_H
