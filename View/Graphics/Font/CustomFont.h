//
// Created by Kamil Krawczyk on 27/04/2024.
//

#ifndef CPP_WEATHER_APP_CUSTOMFONT_H
#define CPP_WEATHER_APP_CUSTOMFONT_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class CustomFont {
public:
    sf::Font font;
    CustomFont(std::string filepath = "fonts/arial.ttf");
};


#endif //CPP_WEATHER_APP_CUSTOMFONT_H
