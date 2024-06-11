//
// Created by Kamil Krawczyk on 27/04/2024.
//

#ifndef CPP_WEATHER_APP_INPUT_H
#define CPP_WEATHER_APP_INPUT_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "../Font/CustomFont.h"

class Input : public CustomFont {
using onEnter = void (*)(std::string);
using onKeyUp = void (*)(std::string);

private:
    CustomFont customFont;
    sf::RenderWindow window;
    std::string placeholder;
    
    void setPlaceholder();
    onEnter onEnterHandler;
    onKeyUp onKeyUpHandler;

public:
    float width, height, fontSize;
    sf::Text inputText;
    sf::RectangleShape background;
    Input(float width, float height, onEnter onEnterFunction = {}, onKeyUp = {}, float fontSize = 14.f, std::string placeholder = "");

    void textEntered(sf::Event& event, std::vector<std::string>& errors);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);

};


#endif //CPP_WEATHER_APP_INPUT_H
