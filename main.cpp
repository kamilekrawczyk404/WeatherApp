#include <SFML/Graphics.hpp>
#include "Backend/Weather.h"
#include "Frontend/Graphics/Inputs/Input.h"
#include "Frontend/Graphics/StaticText/StaticText.h"
#include "Frontend/Graphics/Image/Image.h"
#include "Frontend/Graphics/Containers/Div.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include "Frontend/Layout/Layout.h"


Image background("background.jpg");
std::vector<std::string> errors = {""};
nlohmann::json weatherData, additionalInfo;

void getLocation(std::string content) {
    Weather *weather = new Weather(content);
    
    if (!weather->isOk()) {
        errors[0] = weather->errorMessage;
        delete weather;
    } else {
        weatherData = weather->weatherForecast;
        additionalInfo = weather->additionalInfo;
    }
}

int main() {
    setlocale(LC_ALL, "pl_PL");
    std::cout << "ą" << std::endl;
    Layout ui;
    
    // Input width
    float width = 310;
    
    // Main background
    
    sf::RenderWindow window(sf::VideoMode(background.textureSize.x, background.textureSize.y), "Simple Forecast Application");
    
    // Interactive part with user
    Input locationInput(width, 30.f, getLocation, 16.f, "Enter your location");
    locationInput.setPosition(ui.margin, 20.f);
    
    StaticText errorMessage(errors.at(0), 14, sf::Color::Red);
    errorMessage.setPosition(ui.margin + 10.f, 57.5f);
    
    Div section(width + 4.f, 22.f);
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
            
            // we got the information!
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
