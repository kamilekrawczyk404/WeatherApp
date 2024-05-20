//
// Created by Kamil Krawczyk on 13/05/2024.
//

#include "Checkbox.h"

Checkbox::Checkbox(sf::RenderWindow &window, float x, float y, std::string text, bool &isChecked): checkboxImage(isChecked ? "checked.png" : "unchecked.png"), checkboxContainer(checkboxImage.image.getGlobalBounds().width * 0.5f + (text.size() * (16 / 2)), checkboxImage.image.getGlobalBounds().height * 0.5f), position(x, y), label(text, 16) {
    this->checkboxImage.image.setPosition(x, y);
    this->checkboxImage.image.setScale(0.5f, 0.5f);
    
    this->checkboxContainer.properties.setPosition(x, y);
    
    this->checkboxContainer.draw(window);
    this->checkboxImage.draw(window);

    this->label.setPosition(checkboxImage.image.getGlobalBounds().width + x + 5.f, checkboxImage.image.getGlobalBounds().height / 2 - (2 * label.fontSize / 3)  + y);
    this->label.draw(window);
}

void Checkbox::onClick(sf::RenderWindow &window, sf::Event &event, Checkbox &obj, bool &isChecked, bool &userReleasedButton) {
    if (userReleasedButton && event.type == sf::Event::MouseButtonPressed) {
         userReleasedButton = false;
        
        if (event.mouseButton.button == sf::Mouse::Left) {
            // left mouse button was clicked
            sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f objPosition = obj.checkboxContainer.properties.getPosition();
            sf::FloatRect objBounds = obj.checkboxContainer.bounds;
            
            if (mousePosition.x >= objPosition.x && mousePosition.x <= objPosition.x + objBounds.width && mousePosition.y >= objPosition.y && mousePosition.y <= objPosition.y + objBounds.height) {
                std::cout << mousePosition.x << " " <<mousePosition.y << std::endl;
                
                isChecked = !isChecked;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        userReleasedButton = true;
    }
}

