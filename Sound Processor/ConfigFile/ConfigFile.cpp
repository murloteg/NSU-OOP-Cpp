#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string fileName) : fileName_(fileName)
{
    currentLine_ = "";
    currentCommandIndex_ = 0;
}

void ConfigFile::parseFile()
{
    std::string fullPathFile = "../ConfigDirectory/" + fileName_;
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
    try
    {
        if (commands_.empty())
        {
            throw std::invalid_argument("warning: cannot find configuration commands");
        }
    }
    catch (std::exception& exception)
    {
        exception.what();
        return;
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
        temporaryString += static_cast<char>(number % 10);
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
            if (additionalWAVNumbers_.size() != commands_.size())
            {
                additionalWAVNumbers_.push_back(UNDEFINED);
            }
            currentLine_.clear();
            return;
        }

        else if (characterCode == '$')
        {
            additionalWAVNumbers_.push_back(static_cast<int>(getNextNumber(file)));
            currentLine_ += '$';
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

unsigned int ConfigFile::convertCharToDigit(unsigned char character)
{
    return character - '0';
}

unsigned int ConfigFile::getNextNumber(std::fstream &file)
{
    unsigned char character = file.get();
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
            number += convertCharToDigit(character);
        }
        character = file.get();
    }
    return number;
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
            number += static_cast<int>(convertCharToDigit(character));
        }
        ++currentStringIndex;
        character = string[currentStringIndex];
    }
    return number;
}

std::string ConfigFile::getNextCommandAndPrepareArguments()
{
    std::string currentCommand;
    bool successfulReading = false;
    int indexInString = 0;
    while (indexInString < commands_[currentCommandIndex_].size() && !successfulReading)
    {
        unsigned char character = commands_[currentCommandIndex_][indexInString];
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
            currentCommand += static_cast<char>(character);
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
    return secondParameters_[currentCommandIndex_];
}

int ConfigFile::getAdditionalWAVNumbers()
{
    return additionalWAVNumbers_[currentCommandIndex_];
}

ConfigFile::~ConfigFile()
{
    commands_.clear();
    additionalWAVNumbers_.clear();
    firstParameters_.clear();
    secondParameters_.clear();
}
