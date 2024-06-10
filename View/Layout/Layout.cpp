//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Layout.h"
#include "../Graphics/Checkbox/Checkbox.h"
#include "../Graphics/Containers/Circle.h"
#include "Chart.h"

Layout::Layout(std::vector<std::string> countries) : countries(countries) {}

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
    chart(window);

    foreignLanguages(window);
    
    leftSide(window);
    
    rightSide(window);

    bottomSide(window);
}

void Layout::chart(sf::RenderWindow &window) {
    Chart chart(window, this->event, window.getSize().x - leftContainerWidth - rightContainerWidth - (4 * margin), leftContainerHeight, leftContainerWidth + 2 * margin, top - margin / 2, currentDay, currentHour, currentLanguage, weather, countries);
    
    this->currentHour = chart.currentHour;
}

void Layout::foreignLanguages(sf::RenderWindow &window) {
    
    for (int i = 0; i < countries.size(); i++) {
        const float scale = 0.75f;
        
        Image flag(countries.at(i) + ".png");
        flag.image.setScale(scale, scale);
        
        const float     
            flagWidth = flag.image.getGlobalBounds().width,
            flagHeight = flag.image.getGlobalBounds().height;

        Div container(flagWidth, flagHeight - 10.f);
        container.properties.setFillColor(sf::Color::Transparent);
        container.properties.setPosition(i * (container.bounds.width + margin) + leftContainerWidth + margin * 2, margin + 2.5f);

        if (currentLanguage == i) {
            container.properties.setOutlineThickness(3.f);
            container.properties.setOutlineColor(sf::Color(255, 255, 255));
        }
        container.onClick<int>(window, event, currentLanguage, i);

        const sf::Vector2f containerPos = container.properties.getPosition();

        flag.image.setPosition(containerPos.x, containerPos.y - 5.5f);
        
        container.draw(window);
        flag.draw(window);
    }
}

void Layout::leftSide(sf::RenderWindow &window) {
    std::vector<std::string> translatedFeelsLike = {"Odczuwalna", "Feels like", "Abonnieren"};
    
    Div mainSectionContainer(leftContainerWidth, leftContainerHeight);
    mainSectionContainer.properties.setPosition(margin - 2.f, top - 10.f);
    mainSectionContainer.draw(window);

    StaticText location(additionalInfo["city"], 24);
    location.setPosition(margin + 10.f, top + 150.f);
    location.draw(window);

    StaticText feelsLike("", 20.f);
    feelsLike.setPosition(margin + 10.f, top + 125.f);

    StaticText temperature("", 44);
    temperature.setPosition(margin + 120.f, top + 10.f);

    StaticText currentInfo("", 40);
    currentInfo.setPosition(margin + 10.f, top + 80.f);

    if (!currentDay) {
        Image sunrise("sunrise.png");
        sunrise.image.setPosition(margin, top + 175.f);
        sunrise.image.setScale(0.75f, 0.75f);
        sunrise.draw(window);

        StaticText sunriseInfo(additionalInfo["sunrise"], 24);
        sunriseInfo.text.setPosition(margin + 20.f, top + 260.f);
        sunriseInfo.draw(window);

        Image sunset("sunset.png");
        sunset.image.setPosition(margin + 150.f, top + 175.f);
        sunset.image.setScale(0.75f, 0.75f);
        sunset.draw(window);

        StaticText sunsetInfo(additionalInfo["sunset"], 24);
        sunsetInfo.text.setPosition(margin + 170.f, top + 260.f);
        sunsetInfo.draw(window);
    }
    
    std::string
        iconName = weather[currentDay]["data"][currentHour]["weather"]["icon"];
        temperature.text.setString(weather[currentDay]["data"][currentHour]["temperature"]["main"].get<std::string>());
        currentInfo.text.setString(weather[currentDay]["data"][currentHour]["weather"]["info"][currentLanguage][countries[currentLanguage]].get<std::string>());
        feelsLike.text.setString(translatedFeelsLike[currentLanguage] + ": " + weather[currentDay]["data"][currentHour]["temperature"]["feelsLike"].get<std::string>());
        
    CelsiusSign(window, 20, feelsLike.text);

    currentInfo.draw(window);
    temperature.draw(window);
    feelsLike.draw(window);

    CelsiusSign(window, 44, temperature.text);

    Image currentIcon(iconName);
    currentIcon.image.setPosition(margin / 2, top - 20.f);
    currentIcon.draw(window);
}

void Layout::rightSide(sf::RenderWindow &window) {
    Div rightSection (rightContainerWidth, rightContainerHeight);
    rightSection.properties.setPosition(window.getSize().x - rightContainerWidth - margin, margin);
    rightSection.draw(window);

    // tapping on hour in the chart could change the specific information for that part of the day
    for(auto& [key, value] : weather[currentDay]["data"][currentHour]["specificInformation"].items()) {
        int index = std::distance(weather[currentDay]["data"][currentHour]["specificInformation"].begin(), weather[currentDay]["data"][currentHour]["specificInformation"].find(key));
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
    StaticText title(data["title"][countries[currentLanguage]], 20);
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

    StaticText weekday(data["data"][stoi(index)]["weekday"][countries[currentLanguage]], currentDay == i ? 22 : 20);
    weekday.setPosition(offsetLeft + 10.f, offsetTop + 10.f);
    weekday.draw(window);

    Image mainIcon(mainIconName);
    mainIcon.image.setPosition(offsetLeft - 5.f , offsetTop + (isCloudsIcon ? 25.f : 30.f));
    mainIcon.image.setScale(0.75f, 0.75f);
    mainIcon.draw(window);

    StaticText main(mainTemperature, 32);
    main.setPosition(offsetLeft + 90.f, offsetTop + 55.f);
    main.draw(window);

    CelsiusSign(window, 32, main.text);
    
    Image secondaryIcon(secondaryIconName);
    secondaryIcon.image.setPosition(offsetLeft, offsetTop + (isCloudsIcon ? 105.f : 110.f));
    secondaryIcon.image.setScale(0.6f,0.6f);
    secondaryIcon.draw(window);

    StaticText secondary(secondaryTemperature, 24);
    secondary.setPosition(offsetLeft + 70.f, offsetTop + 130.f);
    secondary.draw(window);

    CelsiusSign celsius(window, 24, secondary.text);

    int size = abs(highestTemperature - lowestTemperature);

    float temperatureBarWidth = (stof(mainTemperature) - stof(secondaryTemperature) ) / float (size),
        barOffset = abs(std::min(stoi(mainTemperature), stoi(secondaryTemperature)) - lowestTemperature) / float (size);

    Div temperatureContainer(width - 20.f, 10.f, sf::Vector2f(highestTemperature, lowestTemperature));
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
    if (i != currentDay) {
        singleDayContainer.onClick<int>(window, event, currentDay, i);
    }
}


