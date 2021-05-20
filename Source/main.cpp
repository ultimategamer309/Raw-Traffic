#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>
#include "threader.h"

namespace pt = boost::property_tree;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	//if no json file
	if (!fs::exists("Assets/settings.json")) {
		std::cout << "Error: Deleted json file.\n"
			<< "Please redownload the original json file and put it in the Assets folder.\n\n"
			<< "Terminating . . ." << std::endl;
		return 0;
	}
		

	pt::ptree root;
	pt::read_json("Assets/settings.json", root);
	int hits = root.get<int>("hits", 0);
	int threads = root.get<int>("threads", 0);
	std::string link = root.get<std::string>("link", "NULL");
	std::string proxyFile = root.get<std::string>("proxyList", "NULL");
	int wait = root.get<int>("wait", -1);

	//if anything was deleted notify them
	if (hits == 0) {
		std::cout << "Error: Corrupt json file.\nThe varriable hits is required.\n"
			<< "Please re-add Hits to the json file or redownload the original.\n\n"
			<< "Terminating . . ." << std::endl;
		return 0;
	}
	if (threads == 0) {
		std::cout << "Error: Corrupt json file.\nThe varriable threads is required.\n"
			<< "Please re-add Hits to the json file or redownload the original.\n\n"
			<< "Terminating . . ." << std::endl;
		return 0;
	}
	if (link == "NULL") {
		std::cout << "Error: Corrupt json file.\nThe varriable link is required.\n"
			<< "Please re-add Hits to the json file or redownload the original.\n\n"
			<< "Terminating . . ." << std::endl;
		return 0;
	}
	//don't throw error if proxyList or wait is undeffined
	//just assume value and notify user
	if (proxyFile == "NULL") {
		proxyFile = "Assets/ProxyList.txt";
		std::cout << "Error: Potentally Corrupt json file.\nThe varriable proxyFile is missing.\n"
			<< "This error is not fatal but the value is assumed to be \"Assets/ProxyList.txt\"\n"
			<< "If this was accidential please re-add proxyFile to the json file to stop receiving this warning"
			<< std::endl;
	}
	if (wait < 0) {
		wait = 0;
		std::cout << "Error: Potentally Corrupt json file.\nThe varriable wait is missing or deffined as negative.\n"
			<< "This error is not fatal but the value is assumed to be 0\n"
			<< "If this was accidential please re-add wait to the json file to stop receiving this warning"
			<< std::endl;
	}

	//start program
	threader t(hits, threads, link, proxyFile, wait);
	t.start();

	std::cout << "Press enter to exit . . .";
	std::cin.ignore();
	std::cin.get();
	return 0;
}
