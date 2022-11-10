#include "GameMode.h"

int GameMode::getLengthOfInt(int value)
{
    int length = 0;
    while (value > 0)
    {
        value /= 10;
        ++length;
    }
    return length;
}

std::string GameMode::convertScoreString(const std::string& scoreString)
{
    std::string result;
    for (char symbol : scoreString)
    {
        result += (symbol == '0') ? "C" : "D";
    }
    return result;
}

int GameMode::convertCharToInt(unsigned char symbol)
{
    return symbol - '0';
}
