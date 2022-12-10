#include "SoundController.h"

SoundController::SoundController(std::string wavFileName, std::string configFileName)
{
    wavFileName_ = wavFileName;
    configFileName_ = configFileName;
    parserWav_ = ParserWAV(wavFileName_);
    configFile_ = ConfigFile(configFileName_);
    parserWav_.parseWAV();
    configFile_.parseFile();
    bufferOfSamples_.clear();
    bufferOfSamples_.resize(parserWav_.getSampleRate());
}

void SoundController::debugTest()
{
    this->parserWav_.debugPrintWAV();
    this->configFile_.debugPrint();
}

void SoundController::conversion()
{

}
