#ifndef SOUND_PROCESSOR_PARSERWAV_H
#define SOUND_PROCESSOR_PARSERWAV_H
#include <iostream>
#include <fstream>

class ParserWAV {
public:
	struct WAVHeader
	{
		unsigned int chunkId;
		unsigned int chunkSize;
		unsigned int format;
		unsigned int subchunk1Id;
		unsigned int subchunk1Size;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned int sampleRate;
		unsigned int byteRate;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		unsigned int subchunk2Id;
		unsigned int subchunk2Size;
	};
	ParserWAV(std::string fileName);
	void parseWAV();
	void debugPrintWAV();
    unsigned int getByteRate() const {return wavHeader_.byteRate;};
    int getWAVHeaderLength() const {return minWAVFileHeaderLength_;}
	~ParserWAV() = default;
private:
	WAVHeader wavHeader_{};
	std::string fileName_;
    int minWAVFileHeaderLength_;
	static void convertLittleEndianToBigEndian(unsigned int& value);
};


#endif //SOUND_PROCESSOR_PARSERWAV_H
