//
// Created by Kamil Krawczyk on 13/05/2024.
//

#ifndef CPP_WEATHER_APP_CHECKBOX_H
#define CPP_WEATHER_APP_CHECKBOX_H
#include <SFML/Graphics.hpp>
#include "../Image/Image.h"
#include "../Containers/Div.h"


class Checkbox {
public:
    bool isChecked = false;
    Checkbox(sf::RenderWindow &window, float x, float y);
    
};


#endif //CPP_WEATHER_APP_CHECKBOX_H
