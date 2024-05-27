//
// Created by Kamil Krawczyk on 11/05/2024.
//

#ifndef CPP_WEATHER_APP_LOCATIONIMAGE_H
#define CPP_WEATHER_APP_LOCATIONIMAGE_H
#include <string>
#include "FetchAPI.h"
#include "KEYS.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <fstream>

class LocationImage {
    std::string name;
public:
    sf::Sprite sprite;
    LocationImage(std::string name);
};


#endif //CPP_WEATHER_APP_LOCATIONIMAGE_H
