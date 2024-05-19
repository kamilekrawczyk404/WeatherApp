//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Layout.h"
#include "../Graphics/Checkbox/Checkbox.h"
#include "../Graphics/Containers/Circle.h"

void Layout::loadJson(json weather, json additionalInfo) {
    this->weather = weather;
    this->additionalInfo = additionalInfo;
    this->lowestTemperature = stoi(additionalInfo["lowestTemp"].get<std::string>());
    this->highestTemperature = stoi(additionalInfo["highestTemp"].get<std::string>());
}

void Layout::loadEvent(sf::Event &event) {
    this->event = event;
}

void Layout::drawLayout(sf::RenderWindow &window) {
    Checkbox languageCheckbox(window, 350.f, margin, isForeignLanguageChecked ? "English version" : "Wersja angielska", isForeignLanguageChecked);
    languageCheckbox.onClick(window, event, isForeignLanguageChecked, userReleasedButton);

    chart(window);
    
//    leftSide(window);
    
    rightSide(window);

    bottomSide(window);
}

void Layout::chart(sf::RenderWindow &window) {
    Div chartContainer(window.getSize().x - leftContainerWidth - rightContainerWidth - (4 * margin), leftContainerHeight);
    chartContainer.properties.setPosition(leftContainerWidth + 2 * margin, top - margin);
    chartContainer.draw(window);

    const float lineThickness = 2.5f;
    
    // getting the lowest and the highest temperature of the current day
    int
        lowestTempDuringDay = stoi(weather[currentDay]["data"][weather[currentDay]["min"].get<int>()]["temperature"]["tempMin"].get<std::string>()),
        highestTempDuringDay = stoi(weather[currentDay]["data"][weather[currentDay]["max"].get<int>()]["temperature"]["tempMax"].get<std::string>());

    Div horizontalLine(chartContainer.bounds.width - lineThickness * 2 * margin, lineThickness);
    horizontalLine.properties.setFillColor(sf::Color(32, 32, 32));
    horizontalLine.properties.setPosition(chartContainer.properties.getPosition().x + lineThickness * margin, chartContainer.properties.getPosition().y + chartContainer.bounds.height - lineThickness * margin);
    horizontalLine.draw(window);
    
    Div verticalLine(lineThickness, chartContainer.bounds.height - lineThickness * 2 * margin);
    verticalLine.properties.setFillColor(sf::Color(32, 32, 32));
    verticalLine.properties.setPosition(chartContainer.properties.getPosition().x + lineThickness * margin, chartContainer.properties.getPosition().y + lineThickness * margin);
    verticalLine.draw(window);
    
    // horizontal section of the chart
    // rainfall and snowfall charts, description
    const int 
        denominator = weather[currentDay]["data"].size(),
        density = horizontalLine.bounds.width / denominator;
    
    // storing position of hours and temperatures
    std::vector<float> 
            xPos, 
            yPos,
            yPosDot;
    
    for(auto& [key, value] : weather[currentDay]["data"].items()) {
        int index = stoi(key);
        float
            x = horizontalLine.properties.getPosition().x + index * (horizontalLine.bounds.width / denominator) + (horizontalLine.bounds.width / denominator) / 2,
            y = horizontalLine.properties.getPosition().y - lineThickness;
        
        Div hourIndicator(lineThickness, 4.f * lineThickness);

        xPos.push_back(x);
        
        hourIndicator.properties.setFillColor(sf::Color(32, 32, 32));
        hourIndicator.properties.setPosition(x, y);
        hourIndicator.draw(window);

        std::string
            hourValue = std::to_string(value["hour"].get<int>()),
            popValueAsString = value["weather"]["precipitation"].get<std::string>();
        
        int 
            popValue = stoi(popValueAsString.substr(0, popValueAsString.find('%')));
        
        StaticText hour(hourValue + ":00", 16);
        hour.setPosition(hourIndicator.properties.getPosition().x - hour.text.getString().getSize() * hour.fontSize / 4, chartContainer.properties.getPosition().y + margin);
        hour.draw(window);
        
        StaticText precipitation(popValueAsString, 16);

        // rain or snow % container
        if (popValue != 0) {
            // we've got some precipitation
            
            Div precipitationContainer(horizontalLine.bounds.width / denominator / 2, float (popValue) / 100.f * verticalLine.bounds.height * 0.85f);
            precipitationContainer.properties.setFillColor(sf::Color(72, 202, 228, 255.f / 2));
            precipitationContainer.properties.setPosition(hourIndicator.properties.getPosition().x - precipitationContainer.bounds.width / 2, hourIndicator.properties.getPosition().y - precipitationContainer.bounds.height + margin / 4 - lineThickness);
            precipitationContainer.draw(window);
            
            StaticText fallValue(value["weather"]["fall"], 16);
            fallValue.setPosition(precipitationContainer.properties.getPosition().x - fallValue.text.getString().getSize() / 2 , precipitationContainer.properties.getPosition().y - fallValue.text.getLocalBounds().height - 1.25f * margin);
            fallValue.draw(window);

            precipitation.setPosition(hourIndicator.properties.getPosition().x - precipitation.fontSize / 4 * precipitation.text.getString().getSize(), precipitationContainer.properties.getPosition().y - precipitation.text.getLocalBounds().height - margin / 2.5f);
        } else {
            precipitation.setPosition(hourIndicator.properties.getPosition().x - precipitation.fontSize / 4 * precipitation.text.getString().getSize(), hourIndicator.properties.getPosition().y - 2 * precipitation.text.getGlobalBounds().height);
        }
        
        precipitation.draw(window);

        StaticText description(value["weather"]["description"].get<std::string>(), 14);
        description.setPosition(hourIndicator.properties.getPosition().x, hourIndicator.properties.getPosition().y + precipitation.text.getGlobalBounds().height);
        description.draw(window);
    }

    // vertical section of the chart
    // temperatures, graph
    const int jump = 5;
    int 
        min, 
        max,
        length = 1;

    min = lowestTempDuringDay - (lowestTempDuringDay < 0 ? jump + (lowestTempDuringDay % jump) : (lowestTempDuringDay % jump));
    max = highestTempDuringDay + (highestTempDuringDay < 0 ? -(highestTempDuringDay % jump) : jump - (highestTempDuringDay % jump));
    
    // getting length of the temperature bar
    // if between the lowest and the highest temperature are also other temperatures which are higher by the step
    int pom = min;
    while (pom < max) {
        length++;
        pom += jump;
    }
    
    float 
        minTempY = verticalLine.properties.getPosition().y + verticalLine.bounds.height - 2.f * margin,
        maxTempY = verticalLine.properties.getPosition().y + 2.f * margin;
    
    for (int i = 0; i < length; i++) {
        std::string value = std::to_string(min + i * jump);
        StaticText temperature(value, 16);
        Div temperatureIndicator(lineThickness * 4.f, lineThickness);
        
        float
            x = chartContainer.properties.getPosition().x + margin / 2.5f,
            y = minTempY - i * (abs(maxTempY - minTempY) / (float) length) - temperature.text.getLocalBounds().height;
        
        temperature.setPosition(x, y);
        temperature.draw(window);
        
        temperatureIndicator.properties.setPosition(verticalLine.properties.getPosition().x - temperatureIndicator.bounds.width / 2, y + temperature.text.getLocalBounds().height / 2 + lineThickness);
        temperatureIndicator.properties.setFillColor(sf::Color(32, 32, 32));
        temperatureIndicator.draw(window);

        yPos.push_back(temperatureIndicator.properties.getPosition().y - temperatureIndicator.bounds.height / 2);
        
        CelsiusSign(window, x, y, 16, value);
    }
    
    for (auto& [key, value] : weather[currentDay]["data"].items()) {
        const int
            index = stoi(key),
            currentTemp = stoi(value["temperature"]["main"].get<std::string>());
        const float
                radius = 2.5f;
        
        // first we need to get points y values
        for (auto& [key, value] : weather[currentDay]["data"].items()) {
            float currentTemp = stoi(value["temperature"]["main"].get<std::string>());
            
            const float
                    stepPerOneDegree = (abs(yPos[0] - yPos[yPos.size() - 1])) / (int)((yPos.size() - 1) * jump),
                    y = yPos[0] - (currentTemp - min) * stepPerOneDegree;
            yPosDot.push_back(y);
        }
        
        if (index + 1 != xPos.size()) {
            for (int i = 0; i < (weather[currentDay]["data"].size() - 1) * density; ++i) {
                float 
                    dotBetweenX = xPos[0] + i * (xPos[int ((i + density) / density)] - xPos[int (i / density)]) / density,
                    dotBetweenY = Helpers::LagrangePolynomial(xPos, yPosDot, dotBetweenX);
                
                Circle dotBetween(radius);
                dotBetween.properties.setPosition(dotBetweenX, dotBetweenY);
                
                dotBetween.addFillColorBasedOnTemperature( min + (abs(minTempY - dotBetweenY) / minTempY) * max );
                
//                std::cout << (abs(maxTempY - minTempY) / dotBetweenY)<< std::endl;
                dotBetween.draw(window);
            }
        }
    }
}

void Layout::leftSide(sf::RenderWindow &window) {
    bool hasDay = weather[currentDay].contains("day"), hasNight = weather[currentDay].contains("night");
    
    Div mainSectionContainer(leftContainerWidth, leftContainerHeight);
    mainSectionContainer.properties.setPosition(margin - 2.f, top - 10.f);
    mainSectionContainer.draw(window);

    StaticText location(additionalInfo[0]["city"], 24);
    location.setPosition(margin + 10.f, top + 150.f);
    location.draw(window);

    StaticText feelsLike("", 20.f);
    feelsLike.setPosition(margin + 10.f, top + 125.f);

    StaticText temperature("", 50);
    temperature.setPosition(margin + 120.f, top + 10.f);

    StaticText currentInfo("", 40);
    currentInfo.setPosition(margin + 10.f, top + 80.f);

    Image sunrise("sunrise.png");
    sunrise.image.setPosition(margin, top + 175.f);
    sunrise.image.setScale(0.75f, 0.75f);
    sunrise.draw(window);

    StaticText sunriseInfo(additionalInfo[0]["sunrise"], 24);
    sunriseInfo.text.setPosition(margin + 20.f, top + 260.f);
    sunriseInfo.draw(window);

    Image sunset("sunset.png");
    sunset.image.setPosition(margin + 150.f, top + 175.f);
    sunset.image.setScale(0.75f, 0.75f);
    sunset.draw(window);

    StaticText sunsetInfo(additionalInfo[0]["sunset"], 24);
    sunsetInfo.text.setPosition(margin + 170.f, top + 260.f);
    sunsetInfo.draw(window);

    std::string iconName;
    // only day property is set
    if (hasDay && !hasNight) {
        iconName = weather[currentDay]["day"]["weather"]["icon"];
        temperature.text.setString(weather[currentDay]["day"]["temperature"]["main"].get<std::string>());
        currentInfo.text.setString(weather[currentDay]["day"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
        feelsLike.text.setString("Feels like: " + weather[currentDay]["day"]["temperature"]["feelsLike"].get<std::string>());
    }
        // only night property is set
    else if (!hasDay && hasNight) {
        iconName = weather[currentDay]["night"]["weather"]["icon"];
        temperature.text.setString(weather[currentDay]["night"]["temperature"]["main"].get<std::string>());
        currentInfo.text.setString(weather[currentDay]["night"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
        feelsLike.text.setString("Feels like: " + weather[currentDay]["night"]["temperature"]["feelsLike"].get<std::string>());

    }
        // both properties are set, decide which one should be main 
    else if (hasDay && hasNight) {
        int currentHour = Helpers::getCurrentHour(additionalInfo[0]["timezone"].get<int>());

        if (abs(currentHour - weather[currentDay]["day"]["hour"].get<int>()) < abs(currentHour - weather[currentDay]["night"]["hour"].get<int>())) {
            iconName = weather[currentDay]["day"]["weather"]["icon"];
            temperature.text.setString(weather[currentDay]["day"]["temperature"]["main"].get<std::string>());
            currentInfo.text.setString(weather[currentDay]["day"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
            feelsLike.text.setString("Feels like: " + weather[currentDay]["day"]["temperature"]["feelsLike"].get<std::string>());
        } else {
            iconName = weather[currentDay]["night"]["weather"]["icon"];
            temperature.text.setString(weather[currentDay]["night"]["temperature"]["main"].get<std::string>());
            currentInfo.text.setString(weather[currentDay]["night"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
            feelsLike.text.setString("Feels like: " + weather[currentDay]["night"]["temperature"]["feelsLike"].get<std::string>());
        }
    }

    CelsiusSign(window, margin + 110.f, top + 125.f, 20, feelsLike.text.getString().substring(12, feelsLike.text.getString().getSize() - 12));

    currentInfo.draw(window);
    temperature.draw(window);
    feelsLike.draw(window);

    CelsiusSign(window, margin + 125.f, top + 10.f, 50, temperature.text.getString());

    Image currentIcon(iconName);
    currentIcon.image.setPosition(margin / 2, top - 20.f);
    currentIcon.draw(window);
}

void Layout::rightSide(sf::RenderWindow &window) {
    Div rightSection (rightContainerWidth, rightContainerHeight);
    rightSection.properties.setPosition(window.getSize().x - rightContainerWidth - margin, margin);
    rightSection.draw(window);

    // tapping on hour in the chart could change the specific information for that part of the day
    for(auto& [key, value] : weather[currentDay]["data"][0]["specificInformation"].items()) {
        int index = std::distance(weather[currentDay]["data"][0]["specificInformation"].begin(), weather[currentDay]["data"][0]["specificInformation"].find(key));
        specificInformation(index, window, key, value, rightSection.properties.getPosition());
    }
}

void Layout::bottomSide(sf::RenderWindow &window) {
    for(auto& [key, item] : weather.items()) {
        singleDayCard(key, window, item);
    }
}

void Layout::specificInformation(int& index, sf::RenderWindow &window, std::string key, json& data, sf::Vector2f position) {
    // gap between elements in a column
    // offset from the right side
    const float gap = 75;
    
    if (key == "Wind") {
        Image windDirection(key + "_direction.png");
        windDirection.image.setOrigin(windDirection.image.getLocalBounds().width / 2, windDirection.image.getLocalBounds().height / 2);
        windDirection.image.setRotation(-45.f + (float)data["deg"]);
        windDirection.image.setPosition(position.x + 200.f, position.y + index * gap + 30.f);
        windDirection.image.setScale(0.3f, 0.3f);
        windDirection.draw(window);
    }
    
    Image icon(  key + ".png");
    StaticText title(data["title"][isForeignLanguageChecked ? "english" : "polish"], 20);
    StaticText value(data["value"], 18);
    
    title.setPosition(position.x + 100.f,  position.y + index * gap + (key != "Cloudiness" ? 10.f : 20.f));
    value.setPosition(position.x + 100.f,  position.y + index * gap + (key != "Cloudiness" ? 30.f : 40.f));
    icon.image.setPosition(position.x + (key != "Cloudiness" ? 10.f : -5.f), position.y + index * gap + (key != "Cloudiness" ? 0.f : -10.f));
    icon.image.setScale(key != "Cloudiness" ? 0.5f : 0.75f, key != "Cloudiness" ? 0.5f : 0.75f);
        
    title.draw(window);
    value.draw(window);
    icon.draw(window);
}

void Layout::singleDayCard(std::string index, sf::RenderWindow &window, json &data) {
    int i = stoi(index);
    
    json 
        lowestTempItem = data["data"][data["min"].get<int>()],
        highestTempItem = data["data"][data["max"].get<int>()];
    std::string 
        mainIconName = highestTempItem["weather"]["icon"], 
        mainTemperature = highestTempItem["temperature"]["tempMax"],
        secondaryIconName = lowestTempItem["weather"]["icon"],
        secondaryTemperature = lowestTempItem["temperature"]["tempMin"];

    // "04" is the index for clouds icon
    bool isCloudsIcon = highestTempItem["weather"]["icon"].get<std::string>().substr(0, 2) == "04" || lowestTempItem["weather"]["icon"].get<std::string>().substr(0, 2) == "03";
//    
    const float 
        gap = 20.f, 
        height = 220.f,
        width = (window.getSize().x - (gap * 6.f)) / 5.f, 
        offsetLeft = width * i + (i == 0 ? 0 : gap * i) + gap,
        offsetTop = window.getSize().y - height - margin;

    Div singleDayContainer(width, height);
    singleDayContainer.properties.setPosition(offsetLeft, offsetTop);
    
    // selected day styling
    if (currentDay == i) {
        singleDayContainer.properties.setOutlineThickness(5.f);
        singleDayContainer.properties.setOutlineColor(sf::Color(32, 32, 32));
    }
    singleDayContainer.draw(window);

    StaticText weekday(highestTempItem["weekday"][isForeignLanguageChecked ? "english" : "polish"], currentDay == i ? 22 : 20);
    weekday.setPosition(offsetLeft + 10.f, offsetTop + 10.f);
    weekday.draw(window);

    Image mainIcon(mainIconName);
    mainIcon.image.setPosition(offsetLeft - 5.f , offsetTop + (isCloudsIcon ? 25.f : 30.f));
    mainIcon.image.setScale(0.75f, 0.75f);
    mainIcon.draw(window);

    StaticText main(mainTemperature, 32);
    main.setPosition(offsetLeft + 90.f, offsetTop + 55.f);
    main.draw(window);

    CelsiusSign(window, offsetLeft + 90.f, offsetTop + 55.f, 32, main.text.getString());
    
    Image secondaryIcon(secondaryIconName);
    secondaryIcon.image.setPosition(offsetLeft, offsetTop + (isCloudsIcon ? 105.f : 110.f));
    secondaryIcon.image.setScale(0.6f,0.6f);
    secondaryIcon.draw(window);

    StaticText secondary(secondaryTemperature, 24);
    secondary.setPosition(offsetLeft + 70.f, offsetTop + 130.f);
    secondary.draw(window);

    CelsiusSign celsius(window, offsetLeft + 70.f, offsetTop + 130.f, 24, secondary.text.getString());

    int size = abs(highestTemperature - lowestTemperature);

    float temperatureBarWidth = (stof(mainTemperature) - stof(secondaryTemperature) ) / float (size),
        barOffset = abs(std::min(stoi(mainTemperature), stoi(secondaryTemperature)) - lowestTemperature) / float (size);

    Div temperatureContainer(width - 20.f, 10.f, sf::Vector2i(highestTemperature, lowestTemperature));
    temperatureContainer.properties.setPosition(offsetLeft + 10.f, offsetTop + 200.f);
    temperatureContainer.draw(window);

    Div temperatureBar(temperatureBarWidth * (width - 20.f), 10.f);
    temperatureBar.properties.setPosition(offsetLeft + 10.f + barOffset * (width - 20.f), offsetTop + 200.f);
    temperatureBar.properties.setFillColor(sf::Color::Transparent);
    temperatureBar.draw(window);

    Div leftMask(temperatureBar.properties.getPosition().x - temperatureContainer.properties.getPosition().x, 10.f);
    leftMask.properties.setFillColor(sf::Color(108, 117, 125));
    leftMask.properties.setPosition(offsetLeft + 10.f, offsetTop + 200.f);
    leftMask.draw(window);

    Div rightMask(width - 20.f - leftMask.bounds.width - temperatureBar.bounds.width, 10.f);
    rightMask.properties.setFillColor(sf::Color(108, 117, 125));
    rightMask.properties.setPosition(offsetLeft + 10.f + leftMask.bounds.width + temperatureBar.bounds.width, offsetTop + 200.f);
    rightMask.draw(window);

    // interaction with left mouse button on single day card
    if (i != currentDay && event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2<int> mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2<float> rectPosition = singleDayContainer.properties.getPosition();
            sf::FloatRect rectBounds = singleDayContainer.properties.getLocalBounds();

            if (mousePosition.x >= rectPosition.x && mousePosition.x <= rectPosition.x + rectBounds.width && mousePosition.y >= rectPosition.y && mousePosition.y <= rectPosition.y + rectBounds.height) {
                currentDay = i;
            }
        }
    }
}


