#include <boost/program_options.hpp>
#include "GameController.h"

namespace po = boost::program_options;
using namespace std;

void ConvertSymbolsToUppercase(string& mode)
{
    for (char &symbol : mode)
    {
        symbol -= 32;
    }
}

int main(int argc, char* argv[])
{
    vector<string> strategies;
    string mode;
    int steps;
    string configDirectory;
    string matrixOfGame;
    string scoreMatrix;

    po::options_description description;
    description.add_options()
            ("help", ":Get info about program's arguments.")
            ("name", po::value< vector<string> >(&strategies)->default_value(strategies, "undefined"), ":Input name of one strategy.")
            ("mode", po::value<string>(&mode)->default_value(mode,"detailed"), ":Select simulation mode.")
            ("steps", po::value<int>(&steps)->default_value(0), ":Input number of iterations.")
            ("configDirectory", po::value<string>(&configDirectory)->default_value(configDirectory, "undefined"), ":Select the directory with strategy's configuration files.")
            ("matrixOfGame", po::value<string>(&matrixOfGame)->default_value(matrixOfGame, "undefined"), ":Select the file with game matrix of game.")
            ("scoreMatrix", po::value<string>(&scoreMatrix)->default_value(scoreMatrix, "undefined"), ":Select the file with score matrix.")
            ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);

    if (variablesMap.count("help"))
    {
        cout << description << endl;
        return 1;
    }

    try
    {
        if (variablesMap.count("name"))
        {
            strategies = variablesMap["name"].as< vector<string> >();
            if (strategies.size() < 3)
            {
                throw invalid_argument("[EXCEPTION]: too few strategies.");
            }
        }
    }
    catch (exception& exception)
    {
        cout << exception.what() << endl;
        return -1;
    }

    try
    {
        if (variablesMap.count("mode"))
        {
            mode = variablesMap["mode"].as<string>();
            if (!(mode == "DETAILED" || mode == "detailed" || mode == "FAST" || mode == "fast" || mode == "TOURNAMENT" || mode == "tournament"))
            {
                throw invalid_argument("[EXCEPTION]: incorrect mode.");
            }
            if (mode == "detailed" || mode == "fast" || mode == "tournament")
            {
                ConvertSymbolsToUppercase(mode);
            }
        }
    }
    catch (exception& exception)
    {
        cout << exception.what() << endl;
        return -1;
    }

    try
    {
        if (variablesMap.count("steps"))
        {
            steps = variablesMap["steps"].as<int>();
            if (steps < 0)
            {
                throw invalid_argument("[EXCEPTION]: \"steps\" value is less than 0.");
            }
        }
    }
    catch (exception& exception)
    {
        cout << exception.what() << endl;
        return -1;
    }

    if (variablesMap.count("configDirectory"))
    {
        configDirectory = variablesMap["configDirectory"].as<string>();
    }

    if (variablesMap.count("matrixOfGame"))
    {
        matrixOfGame = variablesMap["matrixOfGame"].as<string>();
    }

    if (variablesMap.count("scoreMatrix"))
    {
        scoreMatrix = variablesMap["scoreMatrix"].as<string>();
    }

    GameController gameController(strategies, mode, steps, configDirectory, scoreMatrix, matrixOfGame);
    gameController.startGame();

    return 0;
}
