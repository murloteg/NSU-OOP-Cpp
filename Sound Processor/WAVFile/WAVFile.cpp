#include "WAVFile.h"

WAVFile::WAVFile(std::string firstOutput, std::string firstInput)
{

}

WAVFile::WAVFile(std::string output)
{

}

void WAVFile::rewriteFile(unsigned int *buffer, int startSeconds)
{
    int currentSeconds = 0;
    while (currentSeconds < startSeconds)
    {
        inputWAV_.read((char*) &buffer, sizeof(buffer));
        outputWAV_.write((char*) &buffer, sizeof(buffer));
        ++currentSeconds;
    }
}
