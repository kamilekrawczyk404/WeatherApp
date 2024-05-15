//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Layout.h"
#include "../Graphics/Checkbox/Checkbox.h"

void Layout::loadJson(json weather, json additionalInfo) {
    this->weather = weather;
    this->additionalInfo = additionalInfo;
}

void Layout::loadEvent(sf::Event &event) {
    this->event = event;
}

void Layout::drawLayout(sf::RenderWindow &window) {
    Checkbox languageCheckbox(window, 350.f, margin, isForeignLanguageChecked ? "English version" : "Wersja angielska", isForeignLanguageChecked);
    languageCheckbox.onClick(window, event, isForeignLanguageChecked, userReleasedButton);

    chart(window);
    
    leftSide(window);
    
    rightSide(window);

    bottomSide(window);
}

void Layout::chart(sf::RenderWindow &window) {
    Div chartContainer(window.getSize().x - leftContainerWidth - rightContainerWidth - (4 * margin), leftContainerHeight);
    chartContainer.properties.setPosition(leftContainerWidth + 2 * margin, top - margin / 2.f);
    chartContainer.draw(window);
    
    const float lineThickness = 2.5f;
    Div horizontalLine(chartContainer.bounds.width - margin, lineThickness);
    horizontalLine.properties.setFillColor(sf::Color(32, 32, 32));
    horizontalLine.properties.setPosition(chartContainer.properties.getPosition().x + margin / 2, chartContainer.properties.getPosition().y + chartContainer.bounds.height - margin / 2);
    horizontalLine.draw(window);
    
    Div verticalLine(lineThickness, chartContainer.bounds.height - margin);
    verticalLine.properties.setFillColor(sf::Color(32, 32, 32));
    verticalLine.properties.setPosition(chartContainer.properties.getPosition().x + margin / 2, chartContainer.properties.getPosition().y + margin / 2);
    verticalLine.draw(window);
    
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
        feelsLike.text.setString("Feels like: " + weather[currentDay]["day"]["temperature"]["feels_like"].get<std::string>());
    }
        // only night property is set
    else if (!hasDay && hasNight) {
        iconName = weather[currentDay]["night"]["weather"]["icon"];
        temperature.text.setString(weather[currentDay]["night"]["temperature"]["main"].get<std::string>());
        currentInfo.text.setString(weather[currentDay]["night"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
        feelsLike.text.setString("Feels like: " + weather[currentDay]["night"]["temperature"]["feels_like"].get<std::string>());

    }
        // both properties are set, decide which one should be main 
    else if (hasDay && hasNight) {
        int currentHour = Helpers::getCurrentHour(additionalInfo[0]["timezone"].get<int>());

        if (abs(currentHour - weather[currentDay]["day"]["hour"].get<int>()) < abs(currentHour - weather[currentDay]["night"]["hour"].get<int>())) {
            iconName = weather[currentDay]["day"]["weather"]["icon"];
            temperature.text.setString(weather[currentDay]["day"]["temperature"]["main"].get<std::string>());
            currentInfo.text.setString(weather[currentDay]["day"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
            feelsLike.text.setString("Feels like: " + weather[currentDay]["day"]["temperature"]["feels_like"].get<std::string>());
        } else {
            iconName = weather[currentDay]["night"]["weather"]["icon"];
            temperature.text.setString(weather[currentDay]["night"]["temperature"]["main"].get<std::string>());
            currentInfo.text.setString(weather[currentDay]["night"]["weather"]["info"][isForeignLanguageChecked ? "english" : "polish"].get<std::string>());
            feelsLike.text.setString("Feels like: " + weather[currentDay]["night"]["temperature"]["feels_like"].get<std::string>());
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
    bool hasDay = weather[currentDay].contains("day");
    
    Div rightSection (rightContainerWidth, rightContainerHeight);
    rightSection.properties.setPosition(window.getSize().x - rightContainerWidth - margin, margin);
    rightSection.draw(window);

    for(auto& [key, value] : weather[currentDay][hasDay ? "day" : "night"]["specificInformation"].items()) {
        int index = std::distance(weather[currentDay][hasDay ? "day" : "night"]["specificInformation"].begin(), weather[currentDay][hasDay ? "day" : "night"]["specificInformation"].find(key));
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
    // "04" is the index for clouds icon
    bool isDay = data.contains("day"), 
         isCloudsIcon = data[isDay ? "day" : "night"]["weather"]["icon"].get<std::string>().substr(0, 2) == "04" || data[isDay ? "day" : "night"]["weather"]["icon"].get<std::string>().substr(0, 2) == "03";
    std::string 
        mainIconName = data[isDay ? "day" : "night"]["weather"]["icon"], 
        mainTemperature = data[isDay ? "day" : "night"]["temperature"][isDay ? "temp_max" : "temp_min"];
    
    const float 
        gap = 20.f, 
        height = 220.f,
        width = (window.getSize().x - (gap * 6.f)) / 5.f, 
        offsetLeft = width * i + (i == 0 ? 0 : gap * i) + gap,
        offsetTop = window.getSize().y - height - margin;

    Div singleDayContainer(width, height);
    singleDayContainer.properties.setPosition(offsetLeft, offsetTop);
    // selected day
    if (currentDay == i) {
        singleDayContainer.properties.setOutlineThickness(5.f);
        singleDayContainer.properties.setOutlineColor(sf::Color(32, 32, 32));
    }
    singleDayContainer.draw(window);
    
    StaticText weekday(data[isDay ? "day" : "night"]["weekday"][isForeignLanguageChecked ? "english" : "polish"], currentDay == i ? 22 : 20);
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
    
    if (data.contains(isDay ? "night" : "day")) {
        std::string secondaryIconName = data[isDay ? "night" : "day"]["weather"]["icon"], secondaryTemperature = data[isDay ? "night" : "day"]["temperature"][isDay ? "temp_min" : "temp_max"];
        
        Image secondaryIcon(secondaryIconName);
        secondaryIcon.image.setPosition(offsetLeft, offsetTop + (isCloudsIcon ? 105.f : 110.f));
        secondaryIcon.image.setScale(0.6f,0.6f);
        secondaryIcon.draw(window);
        
        StaticText secondary(secondaryTemperature, 24);
        secondary.setPosition(offsetLeft + 70.f, offsetTop + 130.f);
        secondary.draw(window);

        CelsiusSign celsius(window, offsetLeft + 70.f, offsetTop + 130.f, 24, secondary.text.getString());
        

        // if both temperatures are set for single day
        int max = std::max(additionalInfo[0]["highestTemp"].get<int>(), additionalInfo[0]["lowestTemp"].get<int>()),
            min = std::min(additionalInfo[0]["highestTemp"].get<int>(), additionalInfo[0]["lowestTemp"].get<int>()),
            size = abs(max - min);

        float temperatureBarWidth = (stof(mainTemperature) - stof(secondaryTemperature) ) / float (size),
            barOffset = abs(std::min(stoi(mainTemperature), stoi(secondaryTemperature)) - min) / float (size);

        Div temperatureContainer(width - 20.f, 10.f, sf::Vector2i(min, max));
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
    }
    
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


