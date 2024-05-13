//
// Created by Kamil Krawczyk on 13/05/2024.
//

#include "Checkbox.h"

Checkbox::Checkbox(sf::RenderWindow &window, float x, float y, bool &isChecked): checkboxImage(isChecked ? "checked.png" : "unchecked.png"), checkboxContainer(checkboxImage.image.getGlobalBounds().width, checkboxImage.image.getGlobalBounds().height), position(x, y) {
    checkboxImage.image.setPosition(x, y);
    checkboxImage.image.setScale(0.75f, 0.75f);
    
    checkboxContainer.properties.setPosition(x, y);
    
    checkboxContainer.draw(window);
    checkboxImage.draw(window);
}

 void Checkbox::onClick(sf::RenderWindow &window, sf::Event &event, bool &isChecked, bool &userReleasedButton) {
    if (userReleasedButton && event.type == sf::Event::MouseButtonPressed) {
         userReleasedButton = false;
        
        if (event.mouseButton.button == sf::Mouse::Left) {
            // left mouse button was clicked
            sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
            
            if (mousePosition.x >= position.x && mousePosition.x <= position.x + checkboxContainer.bounds.width && mousePosition.y >= position.y && mousePosition.y <= position.y + checkboxContainer.bounds.height) {
                isChecked = !isChecked;
            }
        }
    }
     if (event.type == sf::Event::MouseButtonReleased) {
         userReleasedButton = true;
     }
}

