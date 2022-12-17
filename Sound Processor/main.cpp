#include "SoundController.h"
#include "CommandLineParser.h"

int main(int argc, char** argv)
{
    CommandLineParser commandLineParser(argc, argv);
    StatusesOfWork status = commandLineParser.parseCommandLine();
    if (status == HELP_STATUS || status == ERROR_STATUS)
    {
        return 0;
    }

    try
    {
        SoundController soundController(commandLineParser.getAudioFiles(), commandLineParser.getConfigFile());
        soundController.conversion();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return -1;
    }

    return 0;
}
