#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string fileName) : fileName_(fileName)
{
    currentLine_ = "";
    currentCommandIndex_ = 0;
}

void ConfigFile::parseFile()
{
    std::string fullPathFile = "../" + fileName_;
    std::fstream file;
    file.open(fullPathFile, std::fstream::in);
    if (file.is_open())
    {
        int characterCode = file.get();
        while (!file.eof())
        {
            if (characterCode == '#')
            {
                skipUntilNextLine(file);
                getNextCommand(file);
            }

            else
            {
                getNextCommand(file);
            }
            characterCode = file.get();
        }
    }
}

void ConfigFile::skipUntilNextLine(std::fstream &file)
{
    int characterCode;
    while (!file.eof())
    {
        if (characterCode == '\n')
        {
            return;
        }
        characterCode = file.get();
    }
}

void ConfigFile::appendValueToString(std::string &string)
{
    int number = additionalWAVNumbers_.back();
    std::string temporaryString;
    while (number > 0)
    {
        char value = number % 10;
        temporaryString += number;
        number /= 10;
    }
    std::reverse(temporaryString.begin(), temporaryString.end());
    string += temporaryString;
    string += ' ';
}

void ConfigFile::getNextCommand(std::fstream &file)
{

    int characterCode = file.get();
    while (true)
    {
        if (characterCode == '\n' || characterCode == EOF)
        {
            commands_.push_back(currentLine_);
            if (currentLine_.find('$') == std::string::npos)
            {
                additionalWAVNumbers_.push_back(UNDEFINED);
            }
            currentLine_.clear();
            return;
        }

        else if (characterCode == '$')
        {
            additionalWAVNumbers_.push_back(getNextNumber(file));
            appendValueToString(currentLine_);
            characterCode = file.get();
        }

        else
        {
            currentLine_ += static_cast<char>(characterCode);
            characterCode = file.get();
        }
    }
}

bool ConfigFile::isDigit(unsigned char character)
{
    return '0' <= character && character <= '9';
}

unsigned int ConfigFile::getDigit(unsigned char character)
{
    return character - '0';
}

unsigned int ConfigFile::getNextNumber(std::fstream &file)
{
    unsigned char character = file.get();;
    unsigned int number = 0;
    while (!file.eof())
    {
        if (character == ' ' || character == '\n')
        {
            return number;
        }

        if (isDigit(character))
        {
            number *= 10;
            number += getDigit(character);
        }
        character = file.get();
    }
    return number;
}

void ConfigFile::debugPrint()
{
    std::cout << "COMMANDS:" << std::endl;
    for (const auto& command : commands_)
    {
        std::cout << command << std::endl;
    }
    std::cout << "ADDITIONAL WAV:" << std::endl;
    for (auto item : additionalWAVNumbers_)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

unsigned int ConfigFile::getNextNumber(std::string string, int& stringIndex)
{
    int currentStringIndex = stringIndex;
    int number = UNDEFINED;
    unsigned char character = string[currentStringIndex];
    while (currentStringIndex < string.size())
    {
        if ((character == ' ' || character == '\n') && number != UNDEFINED)
        {
            stringIndex = currentStringIndex;
            return number;
        }

        if (isDigit(character))
        {
            number = number < 0 ? 0 : number;
            number *= 10;
            number += getDigit(character);
        }
        ++currentStringIndex;
        character = string[currentStringIndex];
    }
    return number;
}

std::string ConfigFile::prepareAndConvertParameters()
{
    std::string currentCommand;
    bool successfulReading = false;
    unsigned char character;
    int indexInString = 0;
    while (indexInString < commands_[currentCommandIndex_].size() && !successfulReading)
    {
        character = commands_[currentCommandIndex_][indexInString];
        while (true)
        {
            if (character == ' ')
            {
                successfulReading = true;
                break;
            }

            else if (character == '\n')
            {
                throw std::invalid_argument("bad converter arguments");
            }
            currentCommand += character;
            ++indexInString;
            character = commands_[currentCommandIndex_][indexInString];
        }
        ++indexInString;
    }
    int stringIndex = 0;
    firstParameters_.push_back(getNextNumber(commands_[currentCommandIndex_], stringIndex));
    secondParameters_.push_back(getNextNumber(commands_[currentCommandIndex_], stringIndex));
    return currentCommand;
}

unsigned int ConfigFile::getFirstParameter()
{
    if (additionalWAVNumbers_[currentCommandIndex_] == UNDEFINED)
    {
        return firstParameters_[currentCommandIndex_];
    }
    return additionalWAVNumbers_[currentCommandIndex_];
}

unsigned int ConfigFile::getSecondParameter()
{
    unsigned int secondParameter = secondParameters_[currentCommandIndex_];
    return secondParameter;
}

int ConfigFile::getAdditionalWAVNumbers(unsigned int index)
{
    return additionalWAVNumbers_[index];
}
