//
// Created by Kamil Krawczyk on 16/05/2024.
//

#include "Circle.h"

Circle::Circle(float radius, sf::Color fillColor) {
    properties.setRadius(radius);
    properties.setFillColor(fillColor);
}

void Circle::addFillColorBasedOnTemperature(float temp) {
    properties.setFillColor(Helpers::HSLtoRGB(- (temp * (255.f / 70.f)) + (255.f / 1.9f), 1, 0.5));
}

void Circle::draw(sf::RenderWindow &window) {
    window.draw(properties);
}