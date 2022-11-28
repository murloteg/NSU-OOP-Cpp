#ifndef SOUND_PROCESSOR_PARSERWAV_H
#define SOUND_PROCESSOR_PARSERWAV_H
#include <iostream>
#include <fstream>

enum Consts : int
{
	ONE_BYTE = 8
};

class ParserWAV {
private:
	int audioFormat_;
	int numChannels_;
	int sampleRate_;
	int bitsPerSample_;
	int currentPositionInFile_;
	std::string fileName_;
public:
	ParserWAV(int audioFormat, int numChannels, int sampleRate, int bitsPerSample, std::string fileName);
	void parseWAV();
	~ParserWAV() = default;
};


#endif //SOUND_PROCESSOR_PARSERWAV_H
