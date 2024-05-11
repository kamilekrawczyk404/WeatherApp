//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Div.h"

Div::Div(float width, float height, sf::Vector2i gradientValues): width(width), height(height), gradientValues(gradientValues) {
    this->properties.setSize(sf::Vector2f(width, height));
    this->properties.setFillColor(sf::Color(255, 255, 255, 255 / 2 ));
};

void Div::draw(sf::RenderWindow &window) {
    
    // hls, take offset to change values easier 
    if (gradientValues.x != defaultValue && gradientValues.y != defaultValue) {
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(4);
        
        sf::Color leftColor = Helpers::HSLtoRGB(- (this->gradientValues.x * (255.f / 70.f)) + (255.f / 1.5f), 1, 0.5);
        sf::Color rightColor = Helpers::HSLtoRGB(- (this->gradientValues.y * (255.f / 70.f)) + (255.f / 2.f), 1, 0.5);

        vertices[0].position = this->properties.getPosition();
        vertices[3].position = sf::Vector2f(this->properties.getPosition().x, this->properties.getPosition().y + this->height);
        vertices[0].color  = vertices[3].color = leftColor;

        vertices[1].position = sf::Vector2f(this->properties.getPosition().x + this->width, this->properties.getPosition().y);
        vertices[2].position = sf::Vector2f(this->properties.getPosition().x + this->width, this->properties.getPosition().y + this->height);
        vertices[1].color = vertices[2].color = rightColor;
        
        window.draw(vertices);
    }
   
    
    window.draw(this->properties);
}