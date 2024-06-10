//
// Created by Kamil Krawczyk on 09/06/2024.
//

#ifndef CPP_WEATHER_APP_PREDICTLOCATION_H
#define CPP_WEATHER_APP_PREDICTLOCATION_H
#include "nlohmann/json.hpp"
#include "FetchAPI.h"
#include <string>

class PredictLocation : public FetchAPI {
public:
    explicit PredictLocation(std::string &locationPrefix);
};


#endif //CPP_WEATHER_APP_PREDICTLOCATION_H
