#pragma once
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdlib.h>
#include <time.h>

namespace pt = boost::property_tree;

class userAgent
{
public:
	userAgent();
	std::string getAgent();
private:
	std::string jsonFile = "Assets/curl/userAgents.json";

	void readJson();
	std::string getFirefoxAgent();
	std::string getChromeAgent();
	std::string getPlatformInfo();
	std::string getRandomChild(std::string key, std::string os);
	int random(int min, int max);
	int countPtreeChilds(std::string key);

	std::string currentOs = "";
	pt::ptree pt;
	std::string os;
};

