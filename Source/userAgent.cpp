#include "userAgent.h"

namespace pt = boost::property_tree;

userAgent::userAgent() {
	readJson();
}

void userAgent::readJson() {
	pt::read_json(jsonFile, pt);
}

std::string userAgent::getAgent() {
	std::string agent = "";
	std::string browser = getRandomChild("navigator", "");
	if (browser == "chrome")
		agent = getChromeAgent();
	else if (browser == "firefox")
		agent = getFirefoxAgent();
	return agent;
}

std::string userAgent::getFirefoxAgent() {
	std::string agent = "";
	//always starts the same
	agent += "Mozilla / 5.0 ";
	//platform info
	agent += '(' + getPlatformInfo() + ") ";
	//add geko and geko trail
	agent += "Gecko/20100101 ";
	agent += getRandomChild("navigator_version.firefox", "");

	return agent;
}

std::string userAgent::getChromeAgent() {
	std::string agent = "";
	//always starts the same
	agent += "Mozilla / 5.0 ";
	//platform info
	agent += '(' + getPlatformInfo() + ") AppleWebKit/537.36 ";
	//add geko
	agent += "(KHTML, like Gecko) ";
	agent += getRandomChild("navigator_version.firefox", "");

	return agent;
}

std::string userAgent::getPlatformInfo() {
	//variables
	std::string platform = "";
	std::string os;

	//get os
	os = getRandomChild("os", "");
	this->os = os;
	//get os platform
	platform += getRandomChild("os_platform", os);
	//get cpu
	platform += ' ' + getRandomChild("os_cpu", os);

	return platform;
}

int userAgent::countPtreeChilds(std::string key) {
	int count = 0;
	while (true) {
		//try to get valuse
		std::string path = key + '.' + std::to_string(count + 1);
		boost::optional<std::string> test = pt.get_optional<std::string>(path);
		//if it failed break loop
		if (!test.is_initialized())
			break;
		//increase count
		count++;
	}
	return count;
}

std::string userAgent::getRandomChild(std::string key, std::string os) {
	std::string path;
	if (os != "")
		path = key + '.' + os;
	else
		path = key;
	int size = countPtreeChilds(path);
	path = path + '.' + std::to_string(random(1, size));
	return pt.get<std::string>(path);
}

int userAgent::random(int min, int max) {
	//seed
	srand(time(NULL));
	//get random and return
	return (rand() % (max - min + 1) + min);
}