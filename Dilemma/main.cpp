#include <vector>
#include <boost/program_options.hpp>
#include "GameController.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> strategies;
    string mode;
    int steps;
    string configDirectory;
    string matrix;

    po::options_description description;
    description.add_options()
            ("help", ":Get info about program's arguments.")
            ("name", po::value< vector<string> >(&strategies)->default_value(strategies, "undefined"), ":Input name of one strategy.")
            ("mode", po::value<string>(&mode)->default_value(mode,"detailed"), ":Select simulation mode.")
            ("steps", po::value<int>(&steps)->default_value(0), ":Input number of iterations.")
            ("configDirectory", po::value<string>(&configDirectory)->default_value(configDirectory, "undefined"), ":Select the directory with strategy's configuration files.")
            ("matrix", po::value<string>(&matrix)->default_value(matrix, "undefined"), ":Select the file with game matrix.")
            ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);

    if (variablesMap.count("help"))
    {
        cout << description << endl;
        return 1;
    }

    if (variablesMap.count("name"))
    {
        strategies = static_cast<vector <string> > (variablesMap["name"].as< vector<string> >());
    }

    if (variablesMap.count("mode"))
    {
        mode = variablesMap["mode"].as<string>();
        if (!(mode == "DETAILED" || mode == "FAST" || mode == "TOURNAMENT"))
        {
            throw invalid_argument("incorrect mode");
        }
    }

    if (variablesMap.count("steps"))
    {
        steps = variablesMap["steps"].as<int>();
    }

    if (variablesMap.count("configDirectory"))
    {
        configDirectory = variablesMap["configDirectory"].as<string>();
    }

    if (variablesMap.count("matrix"))
    {
        matrix = variablesMap["matrix"].as<string>();
    }

    GameController gameController(strategies, mode, steps, configDirectory, matrix);
    gameController.startGame();

    return 0;
}
