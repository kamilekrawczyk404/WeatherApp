//
// Created by Kamil Krawczyk on 20/05/2024.
//

#include "Chart.h"

Chart::Chart(sf::RenderWindow &window, sf::Event &event, float width, float height, float x, float y, int &currentDay, int currentHour, int &currentLanguage, json &weather, std::vector<std::string> &countries) :
    chartContainer(width, height),
    horizontalLine(width - 2 * margin * lineThickness, lineThickness),
    verticalLine(lineThickness, height - 2 * lineThickness * margin),
    denominator(weather[currentDay]["data"].size()),
    density((width - 2 * margin * lineThickness / denominator) / 10),
    step(5),
    currentDay(currentDay),
    currentHour(currentHour),
    weather(weather),
    currentLanguage(currentLanguage),
    countries(countries) {
    
    // Main layout of the chart
    chartContainer.properties.setPosition(x, y);
    chartContainer.draw(window);
    
    verticalLine.properties.setPosition(chartContainer.properties.getPosition().x + lineThickness * margin, chartContainer.properties.getPosition().y + lineThickness * margin);
    verticalLine.properties.setFillColor(linesColor);
    verticalLine.draw(window);
    
    horizontalLine.properties.setPosition(chartContainer.properties.getPosition().x + lineThickness * margin, chartContainer.properties.getPosition().y + chartContainer.bounds.height - lineThickness * margin);
    horizontalLine.properties.setFillColor(linesColor);
    horizontalLine.draw(window);

    // Getting the lowest and the highest temperature of the current day
    lowestDuringDay = stoi(weather[currentDay]["data"][weather[currentDay]["min"].get<int>()]["temperature"]["tempMin"].get<std::string>());
    highestDuringDay = stoi(weather[currentDay]["data"][weather[currentDay]["max"].get<int>()]["temperature"]["tempMax"].get<std::string>());

    // Calculating lowest and the highest limit of the temperature of a single day
    lowerLimit = lowestDuringDay - (lowestDuringDay < 0 ? step + (lowestDuringDay % step) : (lowestDuringDay % step));
    upperLimit = highestDuringDay + (highestDuringDay < 0 ? -(highestDuringDay % step) : step - (highestDuringDay % step));

    // Calculating how many steps should be located inside the temperature bar
    int pom = lowerLimit;
    while (pom < upperLimit) {
        this->tempBarLength++;
        pom += step;
    }

    // Temperatures min and max y axis values
    minTempY = verticalLine.properties.getPosition().y + verticalLine.bounds.height - 2.f * margin,
    maxTempY = verticalLine.properties.getPosition().y;
    
    drawTemperatureBar(window);
    setDotYPositions();

    for(auto& [key, value] : weather[currentDay]["data"].items()) {
        int index = stoi(key);

        drawHourIndicator(window, event, value, index);
    }
    
    for(auto& [key, value] : weather[currentDay]["data"].items()) {
        int index = stoi(key);
        
        drawPolynomialLine(window, index);
    }
    for(auto& [key, value] : weather[currentDay]["data"].items()) {
        int index = stoi(key);
        
        drawPrecipitation(window, value, index);
    }
};

void Chart::setDotYPositions() {
    for (auto& [key, value] : weather[currentDay]["data"].items()) {
        int currentTemp = stoi(value["temperature"]["main"].get<std::string>());
        float
            stepPerOneDegree = (abs(tempYPositions[0] - tempYPositions[tempYPositions.size() - 1])) / (int)((tempYPositions.size() - 1) * step),
            y = tempYPositions[0] - (currentTemp - lowerLimit) * stepPerOneDegree;

        dotYPositions.push_back(y);
    }
}

void Chart::drawTemperatureBar(sf::RenderWindow &window) {
    for (int i = 0; i < tempBarLength; i++) {
        std::string value = std::to_string(lowerLimit + i * step);
        
        StaticText temperature(value, 16);
        Div temperatureIndicator(lineThickness * 4.f, lineThickness);
        
        // Coordinates for each temperature
        float
            x = chartContainer.properties.getPosition().x + margin / 2.5f,
            y = minTempY - i * (abs(maxTempY - minTempY) / (float) tempBarLength) - temperature.text.getLocalBounds().height;

        temperature.setPosition(x, y);
        temperature.draw(window);

        temperatureIndicator.properties.setPosition(verticalLine.properties.getPosition().x - temperatureIndicator.bounds.width / 2, y + temperature.text.getLocalBounds().height / 2 + lineThickness);
        temperatureIndicator.properties.setFillColor(linesColor);
        temperatureIndicator.draw(window);

        tempYPositions.push_back(temperatureIndicator.properties.getPosition().y - temperatureIndicator.bounds.height / 2);

        CelsiusSign(window, x, y, 16, value);
    }
}

void Chart::drawPrecipitation(sf::RenderWindow &window, json &item, int &index) {
    std::string popValueAsString = item["weather"]["precipitation"].get<std::string>();
    int popValue = stoi(popValueAsString.substr(0, popValueAsString.find('%')));
    
    StaticText precipitation(popValueAsString.substr(0, popValueAsString.find('.')) + "%", 16);
    
    // Fall container
    if (popValue != 0) {
        // There is some fall
        Div precipitationContainer(horizontalLine.bounds.width / denominator / 4, float (popValue) / 100.f * verticalLine.bounds.height * 0.85f);
        precipitationContainer.properties.setFillColor(sf::Color(72, 202, 228));
        precipitationContainer.properties.setPosition(dotXPositions[index] - precipitationContainer.bounds.width / 2, horizontalLine.properties.getPosition().y - precipitationContainer.bounds.height + margin / 4 - 2 * lineThickness);
        precipitationContainer.draw(window);

        StaticText fallValue(item["weather"]["fall"], 16);
        fallValue.setPosition(precipitationContainer.properties.getPosition().x - fallValue.fontSize / 4 * fallValue.text.getString().getSize() / 2 , precipitationContainer.properties.getPosition().y - fallValue.text.getLocalBounds().height - 1.25f * margin);
        fallValue.draw(window);

        precipitation.setPosition(dotXPositions[index] - precipitation.fontSize / 4 * precipitation.text.getString().getSize(), precipitationContainer.properties.getPosition().y - precipitation.text.getLocalBounds().height - margin / 2.5f);
    } else {
        precipitation.setPosition(dotXPositions[index] - precipitation.fontSize / 4 * precipitation.text.getString().getSize(), horizontalLine.properties.getPosition().y - 2 * precipitation.text.getGlobalBounds().height);
    }

    precipitation.draw(window);
}

void Chart::drawHourIndicator(sf::RenderWindow &window, sf::Event &event, json &item, int &index) {
    std::string
        hourValue = std::to_string(item["hour"].get<int>()),
        descriptionText = item["weather"]["description"][currentLanguage][countries[currentLanguage]].get<std::string>();
    float
        hourX = horizontalLine.properties.getPosition().x + index * (horizontalLine.bounds.width / denominator) + lineThickness + 2.5f * margin,
        hourY = horizontalLine.properties.getPosition().y - lineThickness;

    dotXPositions.push_back(hourX);

    Div hourIndicator(lineThickness, 4.f * lineThickness);
    hourIndicator.properties.setFillColor(sf::Color(32, 32, 32));
    hourIndicator.properties.setPosition(hourX, hourY);
    hourIndicator.draw(window);

    StaticText hour(hourValue + ":00", 16);
    hour.setPosition(hourIndicator.properties.getPosition().x - hour.text.getString().getSize() * hour.fontSize / 4, chartContainer.properties.getPosition().y + margin);
    
    Div hourContainer(50.f, hour.text.getLocalBounds().height + margin / 3);
    hourContainer.properties.setPosition(hourX - hourContainer.bounds.width / 2, chartContainer.properties.getPosition().y + margin);
    hourContainer.properties.setFillColor(sf::Color::White);
    
    if (currentHour == index) {
        hourContainer.properties.setOutlineThickness(lineThickness);
        hourContainer.properties.setOutlineColor(linesColor);
    }
    
    hourContainer.draw(window);
    hour.draw(window);

    StaticText description(descriptionText, 14);
    description.setPosition(hourIndicator.properties.getPosition().x - description.text.getLocalBounds().width / 2, hourIndicator.properties.getPosition().y + margin / 2 );
    description.draw(window);
    
    hourContainer.onClick(window, event, currentHour, index);
}

void Chart::drawPolynomialLine(sf::RenderWindow &window, int &index) {
    const float radius = 2.5f;

    if (index + 1 != dotXPositions.size()) {
        for (int i = 0; i < (weather[currentDay]["data"].size() - 1) * density; ++i) {
            float 
                dotBetweenX = dotXPositions[0] + i * (dotXPositions[int ((i + density) / density)] - dotXPositions[int (i / density)]) / density,
                dotBetweenY = Helpers::LagrangePolynomial(dotXPositions, dotYPositions, dotBetweenX),
                temperature = lowerLimit + (abs(minTempY - dotBetweenY) / minTempY) * upperLimit;

            // a single line instead of linear gradient
//            Circle dotBetween(radius);
//            dotBetween.properties.setPosition(dotBetweenX, dotBetweenY);
//            dotBetween.addFillColorBasedOnTemperature(temperature);
//            dotBetween.draw(window);

            Div gradientBox(radius, horizontalLine.properties.getPosition().y + horizontalLine.bounds.height - dotBetweenY - lineThickness, sf::Vector2f(temperature, temperature));
            gradientBox.fadeIn = true;
            gradientBox.properties.setPosition(dotBetweenX, dotBetweenY);
            gradientBox.draw(window);
        }
    }
}

