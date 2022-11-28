#include "ParserWAV.h"

ParserWAV::ParserWAV(int audioFormat, int numChannels, int sampleRate, int bitsPerSample, std::string fileName) :
													audioFormat_(audioFormat), numChannels_(numChannels), sampleRate_(sampleRate),
													bitsPerSample_(bitsPerSample), currentPositionInFile_(0), fileName_(fileName) {}

void ParserWAV::parseWAV()
{
	std::ifstream file("../" + fileName_);
	if (file.is_open())
	{
		int currentCharCode;
		while (!file.eof())
		{
			currentCharCode = file.get();
			if (currentPositionInFile_ >= 20 && currentPositionInFile_ <= 21)
			{
				audioFormat_ = audioFormat_ << ONE_BYTE;
				audioFormat_ += currentCharCode;
			}

			// TODO: MONO, SAMPLE_RATE, BPS.
		}
	}
}

