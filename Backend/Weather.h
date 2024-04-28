//
// Created by Kamil Krawczyk on 25/04/2024.
//

#ifndef CPP_WEATHER_APP_WEATHER_H
#define CPP_WEATHER_APP_WEATHER_H

#include <string>
#include <iostream>
#include "Location.h"
#include "FetchAPI.h"
#include "HandleJson.h"
#include <nlohmann/json.hpp>
#include <cmath>
#include <ctime>

class Weather : public Location {
    template<typename T>
    double toCelsius(T fahrenheit, int digits = 10);
    static std::string convertToClockFormat(time_t unix);
public:
    json weatherForecast = json::array();
    Weather(std::string& location);
protected:
    std::string getUrl() override;
};

#endif //CPP_WEATHER_APP_WEATHER_H
