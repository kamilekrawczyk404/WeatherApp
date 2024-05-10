//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_DIV_H
#define CPP_WEATHER_APP_DIV_H
#include <SFML/Graphics.hpp>

class Div {
    bool hasGradients;
public:
    float width, height;
    sf::RectangleShape properties;
    sf::VertexArray vertices;
    Div(float width, float height, bool hasGradients = false);
    void draw(sf::RenderWindow& window);
};


#endif //CPP_WEATHER_APP_DIV_H
