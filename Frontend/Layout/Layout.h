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
    sf::Event event;
    bool 
        isForeignLanguageChecked = true,
        userReleasedButton = true;
    int 
        highestTemperature, 
        lowestTemperature;
    std::vector<std::string> countries;
protected:
    float
        leftContainerWidth = 250.f,
        leftContainerHeight = 310.f,
        rightContainerWidth = 250.f,
        rightContainerHeight = 370.f;
    json 
        weather, 
        additionalInfo;
public:
    float 
        margin = 20.f, 
        top = 90.f;
    int 
        currentDay = 0,
        currentHour = 0,
        currentLanguage = 0;
    
    Layout(std::vector<std::string> countries);
    
    void drawLayout(sf::RenderWindow& window);
    void loadJson(json weather, json additionalInfo);
    void loadEvent(sf::Event& event);
    
    void leftSide(sf::RenderWindow& window);
    void rightSide(sf::RenderWindow& window);
    void bottomSide(sf::RenderWindow& window);
    void chart(sf::RenderWindow& window);
    void foreignLanguages(sf::RenderWindow &window);
    
    void specificInformation(int& index, sf::RenderWindow& window, std::string key, json& data, sf::Vector2f position);
    void singleDayCard(std::string index, sf::RenderWindow& window, json& data);
};


#endif //CPP_WEATHER_APP_LAYOUT_H
