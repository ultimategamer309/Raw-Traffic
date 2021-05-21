#include "threader.h"

threader::threader(int hits, int threads, std::string link, std::string listPath, int wait) {
	this->wait = wait;
	this->threads = threads;
	this->hits = hits;
	hitsPerThread = ceil(hits / threads);
	this->link = link;
	this->listPath = listPath;
}

void threader::start() {
	boost::asio::thread_pool pool(threads + 1);
	boost::asio::post(pool, boost::bind(&threader::printProg, hits, pause));
	for (int i = 0; i < hits; i++) {
		boost::asio::post(pool, boost::bind(&threader::ping, link, listPath, hitsPerThread, wait));
	}
	pool.join();
}

void threader::ping(std::string link,
					std::string listPath,
					int hitsPerThread,
					int wait) {
	app a(link, listPath, wait);
	a.loop(hitsPerThread);
}

void threader::printProg(int hits, int pause) {
	while (threader::counter < hits) {
		threader::counterMutex.lock();
		std::cout << "Progress: " << double(threader::counter / hits) * 100
			<< "% (" << threader::counter << " / " << hits << ')' << std::endl;
		threader::counterMutex.unlock();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(pause));
	}
}
