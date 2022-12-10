#ifndef SOUND_PROCESSOR_CONFIGFILE_H
#define SOUND_PROCESSOR_CONFIGFILE_H
#include <iostream>
#include <fstream>
#include <vector>

enum Consts
{
    UNDEFINED = 0
};

class ConfigFile {
private:
    std::string fileName_;
    std::string currentLine_;
    std::vector<std::string> commands_;
    unsigned int currentConverterIndex_;
    unsigned int additionalConverterNumber_;
    void skipUntilNextLine(std::ifstream& file);
    void getNextCommand(std::ifstream& file);
//    void findNextConverter();
//    void createConverterFromString(std::string stringCommand);
    static unsigned int getNextNumber(std::ifstream& file);
    static unsigned int getNextNumber(std::string string);
    static unsigned int getDigit(unsigned char character);
public:
    ConfigFile(std::string fileName);
    void parseFile();
    ~ConfigFile() = default;
    void debugPrint();
};


#endif //SOUND_PROCESSOR_CONFIGFILE_H
