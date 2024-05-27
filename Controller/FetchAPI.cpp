//
// Created by Kamil Krawczyk on 26/04/2024.
//

#include "FetchAPI.h"

FetchAPI::FetchAPI(std::string url): apiUrl(url) {
    curl_easy_setopt(curl, CURLOPT_URL, this->apiUrl.c_str());
    
    this->fetchData();
}

FetchAPI::FetchAPI() {}

size_t FetchAPI::writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
};

void FetchAPI::fetchData() {
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::string response_string;
        std::string header_string;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FetchAPI::writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        char* url;
        long response_code;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
        
        if (res != CURLE_OK) {
            this->errorMessage = "Check your network connection";
            
            throw this->errorMessage;
        }
        if (nlohmann::json::parse(response_string)["status"] == "ZERO_RESULTS") {
            this->errorMessage = "We can't find provided location";

            throw this->errorMessage;
        }

        this->fetchedData = nlohmann::json::parse(response_string);
    }
}