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
#include "Controller/SuggestLocation.h"
#include <algorithm>

std::vector<std::string> 
    errors = {""},
    countries = {"en", "pl", "de"};
nlohmann::json 
    weatherData, 
    additionalInfo, 
    predictedLocations;

void getPredictionsOfLocations(std::string content) {
    const int MINIMUM_LENGTH_FOR_START_SEARCHING = 3;
    std::string encodedString = Helpers::urlEncode(content);

    predictedLocations["predictions"] = {};
    weatherData = {};

    if (content.size() >= MINIMUM_LENGTH_FOR_START_SEARCHING) {
        auto *locations = new SuggestLocation(encodedString);

//        std::cout << "mm";
        if (!locations->isOk()) {
            std::cout << "error" << std::endl;
            errors[0] = locations->errorMessage;
            delete locations;
        } else {
            predictedLocations = locations->fetchedData;
        }
    }
}

void getLocation(std::string content) {
    auto *weather = new Weather(content, countries);

    if (!weather->isOk()) {
        errors[0] = weather->errorMessage;
        delete weather;
    } else {
        weatherData = weather->weatherForecast;
        additionalInfo = weather->additionalInfo;
    }
}

int main() {
    float inputWidth = 250.f;


    Layout ui(countries);
    Image background("background.jpg");
    
    sf::RenderWindow window(sf::VideoMode(background.textureSize.x, background.textureSize.y), "Simple Forecast Application");

    Input locationInput(inputWidth, 30.f, getLocation, getPredictionsOfLocations, 16.f, "Enter your location");
    locationInput.setPosition(ui.margin, 20.f);

    StaticText errorMessage(errors.at(0), 14, sf::Color::Red);
    errorMessage.setPosition(ui.margin + 10.f, 57.5f);

    Div section(inputWidth + 4.f, 22.f);
    section.properties.setPosition(ui.margin - 2, 55.f);

    // main app loop
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
        locationInput.draw(window);

        // while fetching data an error occurred
        if (errors[0].size() != 0) {
            section.draw(window);
            errorMessage.setText(errors.at(0));
            errorMessage.draw(window);
        }
        // weather api returned some data
        else if (!weatherData.empty()) {
            ui.loadJson(weatherData, additionalInfo);
            ui.loadEvent(event);
            ui.drawLayout(window);
            
            locationInput.inputText.setString(additionalInfo["locationName"].get<std::string>());
        }
        // otherwise display predicted locations
        else {
            int i = 0;
            const float height = 25.f;

            for (auto item  : predictedLocations["predictions"]) {
                std::string 
                    locationValue = item["description"].get<std::string>(),
                    onlyMainLocation = item["structured_formatting"]["main_text"].get<std::string>();
                locationValue.erase(std::remove_if(locationValue.begin(), locationValue.end(), ::isspace), locationValue.end());
                locationValue.erase(std::remove(locationValue.begin(), locationValue.end(), ','), locationValue.end());

                StaticText predictedLocation(item["description"].get<std::string>(), 14);
                predictedLocation.setPosition(locationInput.background.getPosition().x + 10.f, locationInput.background.getPosition().y + locationInput.background.getGlobalBounds().height + height / 2 + i * ( height / 4 + height));

                Div predictedContainer(predictedLocation.text.getGlobalBounds().width + 20.f, height);
                predictedContainer.properties.setFillColor(sf::Color(255, 255,255));
                predictedContainer.properties.setPosition(predictedLocation.text.getPosition().x - 10.f, predictedLocation.text.getPosition().y - predictedLocation.text.getLocalBounds().height / 3);

                predictedContainer.onClick<std::string>(window, event, getLocation, onlyMainLocation);
                predictedContainer.draw(window);
                predictedLocation.draw(window);

                i++;
            }
        }
        
        window.display();
    }

    return 0;
}


