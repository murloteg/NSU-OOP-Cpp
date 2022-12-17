#ifndef SOUND_PROCESSOR_PARSERWAVHEADER_H
#define SOUND_PROCESSOR_PARSERWAVHEADER_H
#include <iostream>
#include <fstream>

enum WAVHeaderConsts
{
    MIN_HEADER_SIZE = 44,
    RIFF = 0x52494646,
    WAVE = 0x57415645,
    FMT = 0x666d7420
};

class ParserWAVHeader {
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
	explicit ParserWAVHeader(std::string fileName);
	void parseWAVHeader();
    unsigned int getByteRate() const {return wavHeader_.byteRate;};
    int getWAVHeaderLength() const {return minWAVFileHeaderLength_;}
	~ParserWAVHeader() = default;
private:
	WAVHeader wavHeader_{};
	std::string fileName_;
    int minWAVFileHeaderLength_;
	static void convertLittleEndianToBigEndian(unsigned int& value);
};


#endif //SOUND_PROCESSOR_PARSERWAVHEADER_H
