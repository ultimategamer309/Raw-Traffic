#include "app.h"
#include "threader.h"
//inits
app::app(std::string link, std::string listPath, int wait) {
	set(link, listPath, wait);
}
void app::set(std::string link, std::string listPath, int wait) {
	this->link = link;
	this->wait = wait;
	if (listPath == "")
		useAPI = false;
	else
		useAPI = true;
	this->listPath = listPath;

	newProxy();
}

void app::loop(int times) {
	for (int i = times; i <= times; i++) {
		curl();
		threader::counterMutex.lock();
		threader::counter++;
		threader::counterMutex.unlock();
		newProxy();
	}
}

bool app::curl() {
	bool ret = true;
	CURL* curl_;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl_ = curl_easy_init();
	if (curl_)
	{
		curl_easy_setopt(curl_, CURLOPT_PROXY, proxy.c_str());
		curl_easy_setopt(curl_, CURLOPT_URL, link.c_str());
		curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 1L);
		curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 1L);
		curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl_, CURLOPT_VERBOSE, 0L);
		
		//we only want to follow location if trying to simmulate streaming
		if (wait > 0) {
			curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, true);
		}

		res = curl_easy_perform(curl_);

		curl_easy_cleanup(curl_);

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			curl_easy_cleanup(curl_);
			ret = false;
		}
		curl_global_cleanup();
	}
	return ret;
}

//proxy
void app::newProxy() {
		newProxyFromList();
}

void app::newProxyFromList() {
	try {
		if (proxyList.size() == 0) {
			std::ifstream file(listPath);
			std::string tp;
			while (getline(file, tp)) {
				proxyList.emplace_back(tp);
			}
			file.close();
		}
		app::listMutex.lock();
		proxy = proxyList[app::listProg];
		app::listProg++;
		if (app::listProg >= proxyList.size() - 1)
			app::listProg = 0;
		app::listMutex.unlock();
	}
	catch (int e) {
		//if it fails to read file use api
		std::cout << "failed with: " << e << "\n\n\n";
		std::cout << "trying with api" << std::endl;
	}
}

size_t app::write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	return size * nmemb;
}