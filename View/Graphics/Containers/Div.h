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
public:
    bool fadeIn = false;
    sf::FloatRect bounds;
    sf::RectangleShape properties;
    sf::VertexArray vertices;
    Div(float width, float height, sf::Vector2f gradientValues = sf::Vector2f());
    void draw(sf::RenderWindow& window);

    template<typename T>
    void onClick(sf::RenderWindow &window, sf::Event &event, void fun(T), T &content) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f divPosition = this->properties.getPosition();
                sf::FloatRect divBounds = this->properties.getLocalBounds();

                if (mousePosition.x >= divPosition.x && mousePosition.x <= divPosition.x + divBounds.width && mousePosition.y >= divPosition.y && mousePosition.y <= divPosition.y + divBounds.height) {
                    fun(content);
                }
            }
        }
    }
    
    template<typename T>
    void onClick(sf::RenderWindow &window, sf::Event &event, T &oldValue, T &newValue) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f divPosition = this->properties.getPosition();
                sf::FloatRect divBounds = this->properties.getLocalBounds();
                
                if (mousePosition.x >= divPosition.x && mousePosition.x <= divPosition.x + divBounds.width && mousePosition.y >= divPosition.y && mousePosition.y <= divPosition.y + divBounds.height) {
                    oldValue = newValue;
                }
            }
        }
    }
};


#endif //CPP_WEATHER_APP_DIV_H
