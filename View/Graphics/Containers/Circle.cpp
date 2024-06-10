//
// Created by Kamil Krawczyk on 16/05/2024.
//

#include "Circle.h"

Circle::Circle(float radius, sf::Color fillColor) {
    properties.setRadius(radius);
    properties.setFillColor(fillColor);
}

void Circle::addFillColorBasedOnTemperature(float temp) {
    properties.setFillColor(Helpers::convertTemperatureToColor(temp));
}

void Circle::draw(sf::RenderWindow &window) {
    window.draw(properties);
}