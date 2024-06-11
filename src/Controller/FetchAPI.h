//
// Created by Kamil Krawczyk on 26/04/2024.
//

#ifndef CPP_WEATHER_APP_FETCHAPI_H
#define CPP_WEATHER_APP_FETCHAPI_H
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "KEYS.h"

class FetchAPI {
public:
    std::string 
        errorMessage = "", 
        apiUrl = "";
    CURL* curl = curl_easy_init();

    explicit FetchAPI(std::string url);
    FetchAPI();
    void fetchData();
    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);

    nlohmann::json fetchedData;
};


#endif //CPP_WEATHER_APP_FETCHAPI_H
