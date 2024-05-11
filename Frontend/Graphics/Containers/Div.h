//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_DIV_H
#define CPP_WEATHER_APP_DIV_H
#include <SFML/Graphics.hpp>
#include "../../Backend/Helpers.h"

class Div {
    sf::Vector2i gradientValues;
    // abstract default values 
    int defaultValue = 1000;
public:
    float width, height;
    sf::RectangleShape properties;
    sf::VertexArray vertices;
    Div(float width, float height, sf::Vector2i gradientValues = sf::Vector2i(1000, 1000));
    void draw(sf::RenderWindow& window);
};


#endif //CPP_WEATHER_APP_DIV_H
