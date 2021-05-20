#pragma once
#include <boost/asio/thread_pool.hpp>
#include <boost/thread.hpp>
#include <boost/asio/post.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include "app.h"

class threader
{
public:
	threader(int hits, int threads, std::string link, std::string listPath, int wait);
	void start();
	inline static boost::mutex counterMutex;
	inline static int counter = 0;
private:
	static void ping(std::string link,
					std::string listPath,
					int hitsPerThread,
					int wait);
	static void printProg(int hits, int pause);
	int hitsPerThread;
	int hits;
	int threads;
	std::string link;
	std::string listPath;

	//
	int wait;
	int pause = 30000;
};

