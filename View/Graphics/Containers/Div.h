//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_DIV_H
#define CPP_WEATHER_APP_DIV_H
#include <SFML/Graphics.hpp>
#include "../../../Controller/Helpers.h"
#include "../../Layout/Layout.h"

class Div {
    sf::Vector2i gradientValues;
    // abstract default values 
    int defaultValue = 1000;
    
public:
    bool fadeIn = false;
    sf::FloatRect bounds;
    sf::RectangleShape properties;
    sf::VertexArray vertices;
    Div(float width, float height, sf::Vector2f gradientValues = sf::Vector2f(1000, 1000));
    void draw(sf::RenderWindow& window);
    void onClick(sf::RenderWindow &window, sf::Event event, int &toChange, int &index);
};


#endif //CPP_WEATHER_APP_DIV_H
