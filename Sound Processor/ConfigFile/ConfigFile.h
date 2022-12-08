#ifndef SOUND_PROCESSOR_CONFIGFILE_H
#define SOUND_PROCESSOR_CONFIGFILE_H
#include <iostream>
#include <fstream>
#include "../Converters/Converter.h"

class ConfigFile {
private:
    std::string fileName_;
    std::string currentLine_;
    Converter nextConverter_;
    int additionalConverterNumber_;
    void skipUntilNextLine(std::ifstream& file);
    void getNextCommand(std::ifstream& file);
public:
    ConfigFile(std::string fileName);
    void parseFile();
    ~ConfigFile() = default;
};


#endif //SOUND_PROCESSOR_CONFIGFILE_H
