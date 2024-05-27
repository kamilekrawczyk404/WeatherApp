#include <SFML/Graphics.hpp>
#include "Controller/Weather.h"
#include "View/Graphics/Inputs/Input.h"
#include "View/Graphics/StaticText/StaticText.h"
#include "View/Graphics/Image/Image.h"
#include "View/Graphics/Containers/Div.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include "View/Layout/Layout.h"

std::vector<std::string> 
    errors = {""},
    countries = {"pl", "en", "de"};
nlohmann::json weatherData, additionalInfo;

void getLocation(std::string content) {
    Weather *weather = new Weather(content, countries);

    if (!weather->isOk()) {
        errors[0] = weather->errorMessage;
        delete weather;
    } else {
        weatherData = weather->weatherForecast;
        additionalInfo = weather->additionalInfo;
    }
}

int main() {
    Layout ui(countries);

    float inputWidth = 250.f;

    // Main background
    Image background("background.jpg");

    sf::RenderWindow window(sf::VideoMode(background.textureSize.x, background.textureSize.y), "Simple Forecast Application");

    // Interactive part with user
    Input locationInput(inputWidth, 30.f, getLocation, 16.f, "Enter your location");
    locationInput.setPosition(ui.margin, 20.f);

    StaticText errorMessage(errors.at(0), 14, sf::Color::Red);
    errorMessage.setPosition(ui.margin + 10.f, 57.5f);

    Div section(inputWidth + 4.f, 22.f);
    section.properties.setPosition(ui.margin - 2, 55.f);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                locationInput.textEntered(event, errors);
            }
        }

        window.clear();
        background.draw(window);

        if (!weatherData.empty()) {
            // we've got the information!
            ui.loadJson(weatherData, additionalInfo);
            ui.loadEvent(event);
            ui.drawLayout(window);
        } 
        locationInput.draw(window);

        if (errors[0] != "") {
            section.draw(window);
            errorMessage.setText(errors.at(0));
            errorMessage.draw(window);
        }

        window.display();
    }

    return 0;
}


