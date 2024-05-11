//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_CELSIUSSIGN_H
#define CPP_WEATHER_APP_CELSIUSSIGN_H


#include "StaticText.h"

class CelsiusSign {
public:
    CelsiusSign(sf::RenderWindow& window, float x, float y, int fontSize, std::string temperature);
};


#endif //CPP_WEATHER_APP_CELSIUSSIGN_H
