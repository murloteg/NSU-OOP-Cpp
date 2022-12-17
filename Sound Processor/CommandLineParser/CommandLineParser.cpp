#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc, char **argv) : argc_(argc), argv_(argv)
{
    description_.add_options()
            ("help", "get info about options and converters")
            ("wav", po::value<std::vector <std::string> >(), "input next WAV file; the first .wav file in list will be used for output")
            ("config", po::value<std::string>(), "enter a config .txt file with description_ of transformations")
            ;
}

StatusesOfWork CommandLineParser::parseCommandLine()
{
    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc_, argv_, description_), variablesMap);
    if (variablesMap.count("help") || variablesMap.count("h"))
    {
        std::cout << description_ << std::endl;
        ::Description::putDescriptions();
        return HELP_STATUS;
    }

    if (variablesMap.count("wav") || variablesMap.count("WAV"))
    {
        audioFiles_ = variablesMap["wav"].as<std::vector <std::string> >();
        for (auto& item : audioFiles_)
        {
            std::cout << item << std::endl;
        }
    }

    try
    {
        if (audioFiles_.empty())
        {
            throw std::invalid_argument("cannot find WAV files.");
        }
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return ERROR_STATUS;
    }

    if (variablesMap.count("config"))
    {
        configFile_ = variablesMap["config"].as<std::string>();
        std::cout << configFile_ << std::endl;
    }
    return NORMAL_STATUS;
}

CommandLineParser::~CommandLineParser()
{
    audioFiles_.clear();
}
