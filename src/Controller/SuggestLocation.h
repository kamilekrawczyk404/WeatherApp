//
// Created by Kamil Krawczyk on 09/06/2024.
//

#ifndef CPP_WEATHER_APP_SUGGESTLOCATION_H
#define CPP_WEATHER_APP_SUGGESTLOCATION_H
#include "nlohmann/json.hpp"
#include "FetchAPI.h"
#include <string>

class SuggestLocation : public FetchAPI {
public:
    explicit SuggestLocation(std::string &locationPrefix);
    bool isOk();
};


#endif //CPP_WEATHER_APP_SUGGESTLOCATION_H
