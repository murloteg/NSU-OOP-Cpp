#ifndef SOUND_PROCESSOR_WAVFILE_H
#define SOUND_PROCESSOR_WAVFILE_H
#include <iostream>
#include <fstream>

class WAVFile {
private:
    std::fstream inputWAV_;
    std::fstream outputWAV_;
public:
    WAVFile() = default;
    WAVFile(std::string firstOutput, std::string firstInput);
    WAVFile(std::string output);
    void rewriteFile(unsigned int* buffer, int startSeconds);
    ~WAVFile() = default;
};


#endif //SOUND_PROCESSOR_WAVFILE_H
