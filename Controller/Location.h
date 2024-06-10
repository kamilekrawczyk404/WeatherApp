//
// Created by Kamil Krawczyk on 25/04/2024.
//

#ifndef CPP_WEATHER_APP_LOCATION_H
#define CPP_WEATHER_APP_LOCATION_H
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include "FetchAPI.h"
#include "KEYS.h"

class Location  {
    std::string name;
public:
    std::string 
        fullLocationName,
        errorMessage = "";
    
    Location(std::string& name);
    bool isOk();
protected:
    double lat, lon;
    virtual std::string getUrl();
};

#endif //CPP_WEATHER_APP_LOCATION_H
