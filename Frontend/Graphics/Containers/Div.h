//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_DIV_H
#define CPP_WEATHER_APP_DIV_H
#include <SFML/Graphics.hpp>

class Div {
public:
    float width, height;
    sf::RectangleShape properties;
    Div(float width, float height);
    void draw(sf::RenderWindow& window);
};


#endif //CPP_WEATHER_APP_DIV_H
