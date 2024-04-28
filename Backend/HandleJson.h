//
// Created by Kamil Krawczyk on 26/04/2024.
//

#ifndef CPP_WEATHER_APP_HANDLEJSON_H
#define CPP_WEATHER_APP_HANDLEJSON_H
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

using json = nlohmann::json;


class HandleJson {
public:
    json content;
    HandleJson(std::string rawJson);
};


#endif //CPP_WEATHER_APP_HANDLEJSON_H
