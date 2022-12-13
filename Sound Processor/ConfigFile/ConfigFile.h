#ifndef SOUND_PROCESSOR_CONFIGFILE_H
#define SOUND_PROCESSOR_CONFIGFILE_H
#include <iostream>
#include <fstream>
#include <vector>

enum Consts
{
    UNDEFINED = -1
};

class ConfigFile {
private:
    std::string fileName_;
    std::string currentLine_;
    std::vector<std::string> commands_;
    unsigned int currentCommandIndex_;
    std::vector<int> additionalConverterNumbers_;
    std::vector<unsigned int> firstParameters_;
    std::vector<unsigned int> secondParameters_;
    void skipUntilNextLine(std::ifstream& file);
    void getNextCommand(std::ifstream& file);
    static unsigned int getNextNumber(std::ifstream& file);
    static unsigned int getNextNumber(std::string string, int& stringIndex);
    static bool isDigit(unsigned char character);
    static unsigned int getDigit(unsigned char character);
public:
    ConfigFile(std::string fileName);
    void parseFile();
    std::string prepareAndConvertParameters();
    unsigned int getFirstParameter();
    unsigned int getSecondParameter();
    size_t getNumberOfConverters() {return commands_.size();}
    void increaseCurrentCommandIndex_() {++currentCommandIndex_;}
    ~ConfigFile() = default;
    void debugPrint();
};


#endif //SOUND_PROCESSOR_CONFIGFILE_H
