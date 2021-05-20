#pragma once
#include <string>
#include <curl/curl.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

class app {
public:
	//inits
	app(std::string link, std::string listPath, int wait);
	app();
	void set(std::string link, std::string listPath, int wait);
	//loop
	void loop(int times);
	//curl
	bool curl();
private:
	//proxy
	void newProxy();
	void newProxyFromList();

	//curl
	static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);

	//vars
	std::string proxy;
	std::string link;
	std::string listPath;
	std::vector<std::string> proxyList;
	inline static int listProg = 0;
	inline static boost::mutex listMutex;
	bool useAPI;
	boost::mutex mutex;
	int wait
};