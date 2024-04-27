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
#include <vector>
#include <nlohmann/json.hpp>
#include <math.h>
#include <ctime>

class Weather : protected Location {
    template<typename T>
    double toCelsius(T fahrenheit, int digits = 10);
    std::string convertToHoursAndSeconds(time_t unix);
public:
    json weatherForecast = json::array();
    Weather(std::string location);
    
    // Destructor
    ~Weather();
protected:
    std::string getUrl();
};


#endif //CPP_WEATHER_APP_WEATHER_H
