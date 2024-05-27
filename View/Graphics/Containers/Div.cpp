//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Div.h"

Div::Div(float width, float height, sf::Vector2f gradientValues): gradientValues(gradientValues) {
    this->properties.setSize(sf::Vector2f(width, height));
    this->properties.setFillColor(sf::Color(255, 255, 255, 255 / 2 ));
    this->bounds = this->properties.getLocalBounds();
};

void Div::draw(sf::RenderWindow &window) {
    
    // hls, take offset to change values easier 
    if (gradientValues.x != defaultValue && gradientValues.y != defaultValue) {
        vertices.setPrimitiveType(sf::Quads);
        vertices.resize(4);
        
        sf::Color leftColor = Helpers::convertTemperatureToColor(gradientValues.y);
        sf::Color rightColor = Helpers::convertTemperatureToColor(gradientValues.x);

        vertices[0].position = this->properties.getPosition();
        vertices[3].position = sf::Vector2f(this->properties.getPosition().x, this->properties.getPosition().y + this->bounds.height);
        

        vertices[1].position = sf::Vector2f(this->properties.getPosition().x + this->bounds.width, this->properties.getPosition().y);
        vertices[2].position = sf::Vector2f(this->properties.getPosition().x + this->bounds.width, this->properties.getPosition().y + this->bounds.height);

        if (!fadeIn) {
            vertices[0].color  = vertices[3].color = leftColor;
            vertices[1].color = vertices[2].color = rightColor;
        } else {
            vertices[0].color = leftColor;
            vertices[1].color = rightColor;
            vertices[2].color = vertices[3].color = sf::Color(255, 255, 255, 0);
        }
        
        window.draw(vertices);
    }
   
    
    window.draw(this->properties);
}

void Div::onClick(sf::RenderWindow &window, sf::Event event, int &toChange, int &index) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f divPosition = this->properties.getPosition();
            sf::FloatRect divBounds = this->properties.getLocalBounds();

            
            if (mousePosition.x >= divPosition.x && mousePosition.x <= divPosition.x + divBounds.width && mousePosition.y >= divPosition.y && mousePosition.y <= divPosition.y + divBounds.height) {
                
                toChange = index;
            }
        }
    } 
}