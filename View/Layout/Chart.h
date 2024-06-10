//
// Created by Kamil Krawczyk on 20/05/2024.
//

#ifndef CPP_WEATHER_APP_CHART_H
#define CPP_WEATHER_APP_CHART_H
#include "Layout.h"
#include "../Graphics/Containers/Circle.h"

class Chart {
    
    int lowestDuringDay, highestDuringDay, lowerLimit, upperLimit, currentDay, tempBarLength = 1;
    const int denominator, density, step;
    float 
        lineThickness = 2.5f, 
        margin = 20.f,
        minTempY,
        maxTempY;
    sf::Color linesColor = sf::Color(32, 32, 32);
    std::vector<float> tempYPositions, dotXPositions, dotYPositions;
    std::vector<std::string> countries;
    json weather;
    
    void drawTemperatureBar(sf::RenderWindow &window);
    void drawPrecipitation(sf::RenderWindow &window, json &item, int &index);
    void drawHourIndicator(sf::RenderWindow &window, sf::Event &event, json &item, int &index);
    void drawPolynomialLine(sf::RenderWindow &window, int &index);
    void setDotYPositions();
public:
    int currentHour, currentLanguage;
    Div chartContainer, verticalLine, horizontalLine;
    Chart(sf::RenderWindow &window, sf::Event &event, float width, float height, float x, float y, int &currentDay, int currentHour, int &currentLanguage, json &weather, std::vector<std::string> &countries);
};


#endif //CPP_WEATHER_APP_CHART_H
