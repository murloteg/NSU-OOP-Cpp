#include "ConfigFile.h"

ConfigFile::ConfigFile(std::string fileName) : fileName_(fileName)
{
    currentLine_ = "";
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

            }

            else if (character == '$')
            {

            }

            std::cout << character;
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
    unsigned char character;
    while (!file.eof())
    {
        if (character == '\n')
        {
            return;
        }
        character = file.get();
        currentLine_ += character;
    }
}

