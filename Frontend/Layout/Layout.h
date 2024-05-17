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
#include "../../Backend/Helpers.h"

using json = nlohmann::json;

class Layout {
    json weather, additionalInfo;
    sf::Event event;
    bool isForeignLanguageChecked = true, userReleasedButton = true;
    float 
        leftContainerWidth = 250.f,
        leftContainerHeight = 310.f,
        rightContainerWidth = 250.f,
        rightContainerHeight = 370.f;
    int 
        highestTemperature, 
        lowestTemperature;
public:
    float margin = 20, top = 90;
    int currentDay = 0;
    
    void drawLayout(sf::RenderWindow& window);
    void loadJson(json weather, json additionalInfo);
    void loadEvent(sf::Event& event);
    
    void leftSide(sf::RenderWindow& window);
    void rightSide(sf::RenderWindow& window);
    void bottomSide(sf::RenderWindow& window);
    void chart(sf::RenderWindow& window);
    
    void specificInformation(int& index, sf::RenderWindow& window, std::string key, json& data, sf::Vector2f position);
    void singleDayCard(std::string index, sf::RenderWindow& window, json& data);
};


#endif //CPP_WEATHER_APP_LAYOUT_H
