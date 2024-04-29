//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_LAYOUT_H
#define CPP_WEATHER_APP_LAYOUT_H
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Inputs/Input.h"
#include "../Graphics/StaticText/StaticText.h"
#include "../Graphics/Image/Image.h"
#include "../Graphics/Containers/Div.h"
#include "../Graphics/StaticText/CelsiusSign.h"

using json = nlohmann::json;

class Layout {
    json weather, city;
public:
    float margin = 20, top = 90;
    
    void drawLayout(sf::RenderWindow& window);
    void loadJson(json weather, json city);
    
    static void specificInformation(sf::RenderWindow& window, std::string key, json& data);
    void leftSide(json data);
    void rightSide(json data);
    void bottomSide(json data);
    
    void changeData();
};


#endif //CPP_WEATHER_APP_LAYOUT_H
