#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string fileName) : fileName_(fileName)
{
    currentLine_ = "";
    additionalConverterNumber_ = UNDEFINED;
    currentConverterIndex_ = 0;
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
            currentLine_.clear();
            return;
        }

        else if (character == '$')
        {
            additionalConverterNumber_ = getNextNumber(file);
            character = file.get();
        }

        currentLine_ += character;
        character = file.get();
    }
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
        number *= 10;
        number += getDigit(character);
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
    std::cout << additionalConverterNumber_ << std::endl;
}

unsigned int ConfigFile::getNextNumber(std::string string)
{
    int currentStringIndex = 0;
    unsigned int number = 0;
    unsigned char character = string[currentStringIndex];
    while (currentStringIndex < string.size())
    {

        if (character == ' ' || character == '\n')
        {
            return number;
        }
        number *= 10;
        number += getDigit(character);
        character = string[currentStringIndex];
    }
    return number;
}

/*
void ConfigFile::createConverterFromString(std::string stringCommand)
{
    std::string currentCommand;
    unsigned int firstParameter;
    unsigned int secondParameter;
    int indexInString = 0;
    unsigned char character;
    while (indexInString < currentCommand.size())
    {
        character = stringCommand[indexInString];
        while (true)
        {
            if (character == ' ')
            {
                break;
            }
            currentCommand += character;
            ++indexInString;
            character = stringCommand[indexInString];
        }

        firstParameter = getNextNumber(stringCommand);
        secondParameter = getNextNumber(stringCommand);
        break;
    }
    Converter converter = Factory::createConverter(); // TODO: integrate factory.
}
*/

//void ConfigFile::findNextConverter()
//{
//    if (!commands_.empty())
//    {
//        createConverterFromString(commands_[currentConverterIndex_]);
//    }
//}

