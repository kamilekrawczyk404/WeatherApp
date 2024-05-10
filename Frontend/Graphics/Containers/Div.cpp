//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Div.h"

Div::Div(float width, float height, bool hasGradients): width(width), height(height), hasGradients(hasGradients) {
    this->properties.setSize(sf::Vector2f(width, height));
    this->properties.setFillColor(sf::Color(255, 255, 255, 255 / 2 ));
};

void Div::draw(sf::RenderWindow &window) {
    
    // hls, take offset to change values easier 
    if (this->hasGradients) {
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(4);
        
        sf::Color leftColor(72, 202, 228);
        sf::Color rightColor(232, 93, 4);

        vertices[0].position = this->properties.getPosition();
        vertices[3].position = sf::Vector2f(this->properties.getPosition().x, this->properties.getPosition().y + this->properties.getLocalBounds().height);
        vertices[0].color  = vertices[3].color = leftColor;

        vertices[1].position = sf::Vector2f(this->properties.getPosition().x + this->properties.getLocalBounds().width, this->properties.getPosition().y);
        vertices[2].position = sf::Vector2f(this->properties.getPosition().x + this->properties.getLocalBounds().width, this->properties.getPosition().y + this->properties.getLocalBounds().height);
        vertices[1].color = vertices[2].color = rightColor;
        
        window.draw(vertices);
    }
   
    
    window.draw(this->properties);
}