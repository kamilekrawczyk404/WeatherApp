//
// Created by Kamil Krawczyk on 25/04/2024.
//

#ifndef CPP_WEATHER_APP_LOCATION_H
#define CPP_WEATHER_APP_LOCATION_H
#include <string>
#include <iostream>
#include <cstring>
#include "HandleJson.h"
#include "FetchAPI.h"

class Location  {
    std::string API_KEY = "AIzaSyAWtvDfmVQ_tbJPDzPZQ79TNJPXZJiITKg";
    std::string name;
public:
    Location(std::string name);
    ~Location();
protected:
    // storing as a string for able to use in the weather api
    double lat;
    double lon;
    virtual std::string getUrl();
};


#endif //CPP_WEATHER_APP_LOCATION_H
