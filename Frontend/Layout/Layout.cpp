//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Layout.h"

void Layout::drawLayout(sf::RenderWindow &window) {
    
    // Left side
    Div mainSectionContainer(250.f, 200.f);
    StaticText temperature(weather[0]["temperature"]["main"], 50, sf::Color::White);
    StaticText currentInfo(weather[0]["weather"]["info"], 40, sf::Color::White);
    StaticText location(city[0]["city"], 24, sf::Color::White);
    CelsiusSign celsius(window, margin + (float)temperature.text.getString().getSize() * 30 + 120.f, top + 10.f, 50);

    std::string  iconName = weather[0]["weather"]["icon"];
    Image currentIcon(iconName);

    // Different images sizes
    if (iconName == "04d.png" || iconName == "04n.png") {
        currentIcon.image.setScale(0.75f, 0.75f);
        currentIcon.texture.setSmooth(true);
        currentIcon.image.setPosition(margin / 2 + 20.f, top - 10.f);
    } else {
        currentIcon.image.setPosition(margin / 2, top - 20.f);
    }
    mainSectionContainer.properties.setPosition(margin - 2.f, top - 10.f);
    currentInfo.setPosition(margin + 10.f, top + 100.f);

    temperature.setPosition(margin + 120.f, top + 10.f);
    location.setPosition(margin + 10.f, top + 150.f);

    mainSectionContainer.draw(window);
    temperature.draw(window);
    currentInfo.draw(window);
    currentIcon.draw(window);
    location.draw(window);
    
    // Right side
    // humidity, pressure, cloudiness, wind, visibility, fall
    Div rightSection(250.f, 600.f);
    rightSection.properties.setPosition(730.f, margin);
    
    rightSection.draw(window);
    
    for(auto& [key, value] : weather[0]["specificInformation"].items()) {
        specificInformation(window, key, value);
    }
}

void Layout::loadJson(json weather, json city) {
    this->weather = weather;
    this->city = city;
}

void Layout::specificInformation(sf::RenderWindow &window, std::string key, json& data) {
    static float marginTop = 0;
    float gap = 20;
    std::cout << key << data << std::endl;
    
//    Image icon(data);
//    StaticText title();
//    StaticText info();
    
    // 
    marginTop += gap;
}


