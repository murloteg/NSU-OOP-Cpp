#include "ParserWAV.h"

ParserWAV::ParserWAV(std::string fileName) :fileName_(fileName)
{
    minWAVFileHeaderLength_ = 0;
}

void ParserWAV::parseWAV()
{
	std::ifstream file("../" + fileName_);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&wavHeader_), sizeof(wavHeader_));
//        convertLittleEndianToBigEndian(wavHeader_.chunkId);
//        convertLittleEndianToBigEndian(wavHeader_.format);
//        convertLittleEndianToBigEndian(wavHeader_.subchunk1Id);
        minWAVFileHeaderLength_ = 44; // in bytes. FIXME: put it in enum-class.
		std::string currentString;
		while (currentString != "data")
		{
			unsigned char symbol = file.get();
            ++minWAVFileHeaderLength_;
			if (currentString.empty() && symbol == 'd')
			{
				currentString += symbol;
			}

			else if ((currentString.size() == 1 || currentString.size() == 3) && symbol == 'a') // dAta or datA.
			{
				currentString += symbol;
			}

			else if (currentString.size() == 2 && symbol == 't')
			{
				currentString += symbol;
			}

			else
			{
				currentString.clear();
			}
		}
        // TODO: continue work on this chapter.
	}
    file.close();
}

void ParserWAV::debugPrintWAV()
{
	std::cout << wavHeader_.chunkId << std::endl;
	std::cout << wavHeader_.chunkSize << std::endl;
	std::cout << wavHeader_.subchunk1Id << std::endl;
	std::cout << wavHeader_.format << std::endl;
	std::cout << wavHeader_.audioFormat << std::endl;
	std::cout << wavHeader_.numChannels << std::endl;
	std::cout << wavHeader_.sampleRate << std::endl;
	std::cout << wavHeader_.byteRate << std::endl;
	std::cout << wavHeader_.blockAlign << std::endl;
	std::cout << wavHeader_.bitsPerSample << std::endl;
}

void ParserWAV::convertLittleEndianToBigEndian(unsigned int& value)
{
	unsigned int firstPart = (value & 0x000000ff) << 24u;
	unsigned int secondPart = (value & 0x0000ff00) << 8u;
	unsigned int thirdPart = (value & 0x00ff0000) >> 8u;
	unsigned int fourthPart = (value & 0xff000000) >> 24u;

	value = firstPart | secondPart | thirdPart | fourthPart;
}
