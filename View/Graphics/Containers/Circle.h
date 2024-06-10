//
// Created by Kamil Krawczyk on 16/05/2024.
//

#ifndef CPP_WEATHER_APP_CIRCLE_H
#define CPP_WEATHER_APP_CIRCLE_H
#include <SFML/Graphics.hpp>
#include "../../../Controller/Helpers.h"

class Circle {
public:
    sf::CircleShape properties;
    Circle(float radius, sf::Color fillColor = sf::Color(32, 32, 32));
    void addFillColorBasedOnTemperature(float temp);
    void draw(sf::RenderWindow &window);
};


#endif //CPP_WEATHER_APP_CIRCLE_H
