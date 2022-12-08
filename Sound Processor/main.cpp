#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "ParserWAV.h"
#include "ConfigFile.h"

namespace po = boost::program_options;
using namespace std;
int main(int argc, char** argv)
{
	po::options_description description("Options");
	description.add_options()
	("help", "get info about options")
	("wav", po::value<vector <string> >(), "input next WAV file; the first file in list will be used for output")
	("config", po::value<string>(), "enter a config file with description of transformations")
	;

	po::variables_map variablesMap;
	po::store(po::parse_command_line(argc, argv, description), variablesMap);
	vector<string> audioFiles;
	string configFile;

	if (variablesMap.count("help") || variablesMap.count("h"))
	{
		cout << description << endl;
		return 0;
	}

	if (variablesMap.count("wav") || variablesMap.count("WAV"))
	{
		audioFiles = variablesMap["wav"].as<vector <string> >();
		for (auto& item : audioFiles)
		{
			cout << item << endl;
		}
	}

	if (variablesMap.count("config"))
	{
		configFile = variablesMap["config"].as<string>();
		cout << configFile << endl;
	}

	ParserWAV wavFile(audioFiles[1]);
	wavFile.parseWAV();
	wavFile.debugPrintWAV();
    ConfigFile config(configFile);
    config.parseFile();

    return 0;
}
