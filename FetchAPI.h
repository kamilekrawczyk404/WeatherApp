//
// Created by Kamil Krawczyk on 26/04/2024.
//

#ifndef CPP_WEATHER_APP_FETCHAPI_H
#define CPP_WEATHER_APP_FETCHAPI_H
#include <string>
#include <curl/curl.h>


class FetchAPI {
public:
    std::string fetchedData;
    FetchAPI(std::string url);
    static size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data);
};


#endif //CPP_WEATHER_APP_FETCHAPI_H
