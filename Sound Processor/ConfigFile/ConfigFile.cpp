#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string fileName) : fileName_(fileName)
{
    currentLine_ = "";
    currentCommandIndex_ = 0;
}

void ConfigFile::parseFile()
{
    std::string fullPathFile = "../" + fileName_;
    std::ifstream file(fullPathFile);
    if (file.is_open())
    {
        unsigned char character;
        while (!file.eof())
        {
            character = file.get();
            if (character == '#')
            {
                skipUntilNextLine(file);
                getNextCommand(file);
            }

            else
            {
                getNextCommand(file);
            }
        }
    }
}

void ConfigFile::skipUntilNextLine(std::ifstream &file)
{
    unsigned char character;
    while (!file.eof())
    {
        if (character == '\n')
        {
            return;
        }
        character = file.get();
    }
}

void ConfigFile::getNextCommand(std::ifstream &file)
{
    unsigned char character = file.get();
    while (!file.eof())
    {
        if (character == '\n')
        {
            commands_.push_back(currentLine_);
            if (currentLine_.find('$') == std::string::npos)
            {
                additionalConverterNumbers_.push_back(UNDEFINED);
            }
            currentLine_.clear();
            return;
        }

        else if (character == '$')
        {
            currentLine_ += '$';
            currentLine_ += ' ';
            additionalConverterNumbers_.push_back(getNextNumber(file));
            character = file.get();
        }

        else
        {
            currentLine_ += character;
            character = file.get();
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

unsigned int ConfigFile::getNextNumber(std::ifstream &file)
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
    for (auto item : additionalConverterNumbers_)
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
    if (additionalConverterNumbers_[currentCommandIndex_] == UNDEFINED)
    {
        return firstParameters_[currentCommandIndex_];
    }
    return additionalConverterNumbers_[currentCommandIndex_];
}

unsigned int ConfigFile::getSecondParameter()
{
    unsigned int secondParameter = secondParameters_[currentCommandIndex_];
    return secondParameter;
}
