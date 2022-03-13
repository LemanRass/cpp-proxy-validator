#include "cpp-proxy-validator.h"


string targetUrl;
int timeout = 20000;
int threadsCount = 100;
vector<string> validProxies;
vector<string> checkProxies;
vector<thread> threads;


string page;
size_t write_data(char* buffer, size_t size, size_t nmemb, void* userp)
{
    size_t realSize = size * nmemb;

    for (int i = 0; i < realSize; i++) {
        page.push_back(buffer[i]);
    }

    return realSize;
}

Request createRequest(const string& proxy) {

    CURL* curl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, targetUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);

    return { curl };
}

void performRequest(Request& request) {

    curl_easy_perform(request.curl);
    curl_easy_getinfo(request.curl, CURLINFO_RESPONSE_CODE, &request.code);
}

void disposeRequest(Request request) {
    curl_easy_cleanup(request.curl);
}



void writeValidProxiesToFile() {

    FILE* f = fopen("./whitelist.txt", "wt+");

    for (auto& validProxy : validProxies) {
        fputs((validProxy + '\n').c_str(), f);
    }

    fclose(f);
}


void checkProxy() {

    while (!checkProxies.empty()) {

        string proxy = checkProxies.back();
        checkProxies.pop_back();

        auto request = createRequest(proxy);
        performRequest(request);

        if (request.code == 200) {
            validProxies.push_back(proxy);
            Logger::Log("\033[32m[SUCCESS]\033[0m " + proxy);
        }
        else {
            Logger::Log("\033[31m[FAIL]\033[0m " + proxy);
        }
        disposeRequest(request);
    }
}

int main() {

    cout << "Target url [https://google.com]: ";
    getline(cin, targetUrl);
    if (strcmp(targetUrl.c_str(), "") == 0) {
        targetUrl = "https://google.com";
    }


    cout << "Threads count [100]: ";
    string threadsCountInput;
    getline(cin, threadsCountInput);
    if (strcmp(threadsCountInput.c_str(), "") == 0) {
        threadsCount = 100;
    }
    else {
        threadsCount = stoi(threadsCountInput);
    }


    cout << "Timeout [10000]: ";
    string timeoutInput;
    getline(cin, timeoutInput);
    if (strcmp(timeoutInput.c_str(), "") == 0) {
        timeout = 10000;
    }
    else {
        timeout = stoi(timeoutInput);
    }
    cout << endl;

    //cout << targetUrl << " " << threadsCount << " " << timeout << endl;


    ProxyList::Init();
    checkProxies = ProxyList::GetProxies();
    cout << "Loaded " << checkProxies.size() << " proxies." << endl;

    cout << "Checking proxies..." << endl;

    //Correct threads count
    if (checkProxies.size() < threadsCount) {
        threadsCount = (int)checkProxies.size();
    }

    //Creating threads
    for (int i = 0; i < threadsCount; i++) {
        threads.emplace_back(thread(checkProxy));
    }

    //Awaiting threads
    for (auto& thread : threads) {
        thread.join();
    }

    cout << "Valid proxies: " << validProxies.size() << endl;

    //Write valid proxies to file
    writeValidProxiesToFile();

    return 0;
}
