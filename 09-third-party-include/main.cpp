#include <iostream>
#include <curl/curl.h>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char *argv[])
{
    std::cout << "Hello Third Party Include!" << std::endl;
    std::string readBuffer;
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);

      std::cout << readBuffer << std::endl;
    }

   return 0;
}
