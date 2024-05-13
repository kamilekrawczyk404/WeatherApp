//
// Created by Kamil Krawczyk on 13/05/2024.
//

#ifndef CPP_WEATHER_APP_CHECKBOX_H
#define CPP_WEATHER_APP_CHECKBOX_H
#include <SFML/Graphics.hpp>
#include "../Image/Image.h"
#include "../Containers/Div.h"


class Checkbox {
    Image checkboxImage;
    Div checkboxContainer;
    bool userClicked = false;
public:
    sf::Vector2f position;
    Checkbox(sf::RenderWindow &window, float x, float y, bool &isChecked);
    void onClick(sf::RenderWindow &window, sf::Event &event, bool &isChecked, bool &userReleasedButton);
    
};


#endif //CPP_WEATHER_APP_CHECKBOX_H
