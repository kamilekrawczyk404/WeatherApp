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
public:
    using fncPtr = void (*)(std::string);

    sf::RectangleShape background;
    
    Input(float width, float height, fncPtr func, float fontSize = 14.f, std::string placeholder = "");
    
    void textEntered(sf::Event& event, std::vector<std::string>& errors);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
private:
    CustomFont customFont;
    sf::RenderWindow window;
    sf::Text inputText;
    float width, height, fontSize;
    std::string placeholder;
    
    void setPlaceholder();
    void onEnter();
    fncPtr onEnterHandler;
};


#endif //CPP_WEATHER_APP_INPUT_H
