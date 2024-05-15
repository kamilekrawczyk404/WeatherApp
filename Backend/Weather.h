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
#include "HandleJson.h"
#include "Helpers.h"
#include <nlohmann/json.hpp>
#include <cmath>
#include "LocationImage.h"

class Weather : public Location , public LocationImage {
public:
    json weatherForecast, additionalInfo;
    Weather(std::string& location);
protected:
    std::string getUrl() override;
};

#endif //CPP_WEATHER_APP_WEATHER_H
