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
    unsigned int currentCommandIndex_;
    std::vector<std::string> commands_;
    std::vector<int> additionalWAVNumbers_;
    std::vector<unsigned int> firstParameters_;
    std::vector<unsigned int> secondParameters_;
    void getNextCommand(std::fstream& file);
    void appendValueToString(std::string& string);
    static void skipUntilNextLine(std::fstream& file);
    static unsigned int getNextNumber(std::fstream& file);
    static unsigned int getNextNumber(std::string string, int& stringIndex);
    static bool isDigit(unsigned char character);
    static unsigned int convertCharToDigit(unsigned char character);
public:
    explicit ConfigFile(std::string fileName);
    void parseFile();
    std::string getNextCommandAndPrepareArguments();
    unsigned int getFirstParameter();
    unsigned int getSecondParameter();
    int getAdditionalWAVNumbers();
    size_t getNumberOfConverters() {return commands_.size();}
    void increaseCurrentCommandIndex() {++currentCommandIndex_;}
    ~ConfigFile();
};


#endif //SOUND_PROCESSOR_CONFIGFILE_H
