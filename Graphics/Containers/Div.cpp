//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Div.h"

Div::Div(float width, float height): width(width), height(height) {
    this->properties.setSize(sf::Vector2f(width, height));
};

void Div::draw(sf::RenderWindow &window) {
    window.draw(this->properties);
}