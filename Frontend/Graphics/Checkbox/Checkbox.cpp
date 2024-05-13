//
// Created by Kamil Krawczyk on 13/05/2024.
//

#include "Checkbox.h"

Checkbox::Checkbox(sf::RenderWindow &window, float x, float y) {
    Image checkboxImage("checked.png");
    Div checkboxContainer(x, y);

    checkboxImage.image.setPosition(x, y);
    checkboxContainer.properties.setPosition(x, y);
    
    checkboxContainer.draw(window); 
    checkboxImage.draw(window); 
}