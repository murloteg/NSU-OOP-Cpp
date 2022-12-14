#include "ParserWAVHeader.h"

ParserWAVHeader::ParserWAVHeader(std::string fileName) : fileName_(fileName)
{
    minWAVFileHeaderLength_ = 0;
}

void ParserWAVHeader::parseWAVHeader()
{
    std::fstream file("../" + fileName_, std::fstream::in);
    if (!file.is_open())
    {
        throw std::invalid_argument("invalid input WAV file name.");
    }

	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&wavHeader_), sizeof(wavHeader_));
        convertLittleEndianToBigEndian(wavHeader_.chunkId);
        convertLittleEndianToBigEndian(wavHeader_.format);
        convertLittleEndianToBigEndian(wavHeader_.subchunk1Id);
        if (wavHeader_.chunkId != RIFF || wavHeader_.format != WAVE || wavHeader_.subchunk1Id != FMT)
        {
            throw std::invalid_argument("invalid file encoding.");
        }

        minWAVFileHeaderLength_ = MIN_HEADER_SIZE;
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
	}
    file.close();
}

void ParserWAVHeader::convertLittleEndianToBigEndian(unsigned int& value)
{
	unsigned int firstPart = (value & 0x000000ff) << 24u;
	unsigned int secondPart = (value & 0x0000ff00) << 8u;
	unsigned int thirdPart = (value & 0x00ff0000) >> 8u;
	unsigned int fourthPart = (value & 0xff000000) >> 24u;
	value = firstPart | secondPart | thirdPart | fourthPart;
}
