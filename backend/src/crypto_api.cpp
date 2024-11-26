#include "crypto_api.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

double getCryptoPrice(const std::string& cryptoSymbol) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + cryptoSymbol + "&vs_currencies=usd";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "CURL failed: " << curl_easy_strerror(res) << "\n";
            return -1;
        }

        Json::Value jsonData;
        Json::CharReaderBuilder readerBuilder;
        std::string errs;

        if (Json::parseFromStream(readerBuilder, readBuffer, &jsonData, &errs)) {
            return jsonData[cryptoSymbol]["usd"].asDouble();
        } else {
            std::cerr << "Failed to parse JSON: " << errs << "\n";
        }
    }

    return -1;
}
