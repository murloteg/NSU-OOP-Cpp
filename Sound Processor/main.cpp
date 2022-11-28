#include <iostream>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>

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

	string filePath = "../funkorama.wav";
	std::ifstream file(filePath);
	int pos = 0;
	while (!file.eof())
	{
		int temp = file.get();
		cout << temp << " pos: " << pos << endl;
		++pos;
		if (pos > 100)
		{
			return 0;
		}
	}

    return 0;
}

// little-endian
// pos 20-21 : PCM = 1.
// pos 22-23 : MONO = 1.
// pos 24-27 : SAMPLE_RATE = 44100 hz. // 1010 1100 0100 0100
// pos 34-35 : BPS = 16.
//    00000001 00001111 00100001 00010100 : 17 768 724
