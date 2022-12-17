#ifndef SOUND_PROCESSOR_COMMANDLINEPARSER_H
#define SOUND_PROCESSOR_COMMANDLINEPARSER_H
#include "Description.h"
#include <boost/program_options.hpp>

enum StatusesOfWork
{
    HELP_STATUS = 0,
    NORMAL_STATUS = 1,
    ERROR_STATUS = 2
};

namespace po = boost::program_options;
class CommandLineParser {
private:
    int argc_;
    char** argv_;
    po::options_description description_{"Options"};
    std::vector<std::string> audioFiles_;
    std::string configFile_;
public:
    CommandLineParser(int argc, char** argv);
    StatusesOfWork parseCommandLine();
    std::vector<std::string> getAudioFiles() {return audioFiles_;}
    std::string getConfigFile() {return configFile_;}
    ~CommandLineParser();
};


#endif //SOUND_PROCESSOR_COMMANDLINEPARSER_H
