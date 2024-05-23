//
// Created by Kamil Krawczyk on 25/04/2024.
//

#ifndef CPP_WEATHER_APP_WEATHER_H
#define CPP_WEATHER_APP_WEATHER_H

#include <string>
#include <iostream>
#include <sstream>
#include "Location.h"
#include "FetchAPI.h"
#include "Helpers.h"
#include "TranslationAPI.h"
#include <nlohmann/json.hpp>
#include <cmath>
#include "LocationImage.h"


class Weather : public Location , public LocationImage {
public:
    nlohmann::json 
        weatherForecast, 
        additionalInfo, 
        translatedDescriptions, 
        translatedWeatherInfo;
    std::vector<std::string> 
        countries, 
        descriptions, 
        weatherInfo;
    Weather(std::string& location, std::vector<std::string> &countries);
protected:
    std::string getUrl() override;
    nlohmann::json formatData(nlohmann::json &content, nlohmann::json &item);
};

#endif //CPP_WEATHER_APP_WEATHER_H
