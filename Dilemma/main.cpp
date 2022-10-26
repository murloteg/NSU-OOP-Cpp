#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "GameStrategy.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> names;
    string mode;
    int steps;
    vector<string> configs;
    string matrix;

    po::options_description description;
    description.add_options()
            ("help", "Get info about program's arguments.")
            ("names", po::value< vector<string> >(&names)->default_value(names, "undefined"), "Input name of one strategy.")
            ("mode", po::value<string>(&mode)->default_value(mode,"detailed"), "Select simulation type.")
            ("steps", po::value<int>(&steps)->default_value(0), "Input number of iterations.")
            ("configs", po::value< vector<string> >(&configs)->default_value(configs, "undefined"), "Select file with strategy's config.")
            ("matrix", po::value<string>(&matrix)->default_value(matrix, "undefined"), "Select the strategy config file.")
            ;

    po::variables_map variablesMap;
    po::store(po::parse_command_line(argc, argv, description), variablesMap);

    if (variablesMap.count("help"))
    {
        cout << description << endl;
        return 1;
    }

    if (variablesMap.count("names"))
    {
        names = static_cast<vector <string> > (variablesMap["names"].as< vector<string> >());
        for (auto &name : names)
        {
            cout << "Strategy name: " << name << endl;
        }
    }

    if (variablesMap.count("mode"))
    {
        mode = variablesMap["mode"].as<string>();
        if (mode == "detailed" || mode == "fast" || mode == "tournament")
        {
            cout << mode << endl;
        }

        else
        {
            throw invalid_argument("incorrect mode");
        }
    }

    if (variablesMap.count("steps"))
    {
        steps = variablesMap["steps"].as<int>();
        cout << steps << endl;
    }

    if (variablesMap.count("configs"))
    {
        configs = static_cast<vector <string> > (variablesMap["configs"].as< vector<string> >());
        for (auto &config : configs)
        {
            cout << config << endl;
        }
    }

    if (variablesMap.count("matrix"))
    {
        matrix = variablesMap["matrix"].as<string>();
        cout << matrix << endl;
    }

    return 0;
}
