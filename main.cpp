#include <SFML/Graphics.hpp>
#include "Backend/Weather.h"
#include "Graphics/Inputs/Input.h"
#include "Graphics/StaticText/StaticText.h"
#include "Graphics/Image/Image.h"
#include "Graphics/Containers/Div.h"
#include <vector>
#include <nlohmann/json.hpp>

std::vector<std::string> errors = {""};
nlohmann::json weatherData;

void getLocation(std::string content) {
    Weather *weather = new Weather(content);

    if (!weather->isOk()) {
        errors[0] = weather->errorMessage;
        delete weather;
    } else {
        weatherData = weather->weatherForecast;
    }
}

int main() {
    Image background("background.jpg");
    
    Div section(350.f, 150.f);
    section.properties.setFillColor(sf::Color(255, 255, 255, 255 * 3/4));
    section.properties.setPosition((background.textureSize.x - section.properties.getLocalBounds().getSize().x )/ 2, (background.textureSize.y - section.properties.getLocalBounds().getSize().y )/ 2);
    
    sf::RenderWindow window(sf::VideoMode(background.textureSize.x, background.textureSize.y), "Simple Forecast Application");
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;
    
    Input locationInput(300.f, 30.f, getLocation, 14.f, "Enter your location");
    locationInput.setPosition((centerX - locationInput.background.getSize().x / 2), (centerY - locationInput.background.getSize().y / 2));
    
    StaticText title("Weather Forecast Application", 18, sf::Color::Black);
    title.justifyCenter(centerX, centerY, 0, -50.f);
    
    StaticText errorMessage(errors.at(0), 14, sf::Color::Red);
    errorMessage.justifyCenter(centerX, centerY, 0, 40.f);
    
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
        } else {
            section.draw(window);
            locationInput.draw(window);
            title.draw(window);

            if (errors.size()) {
                errorMessage.setText(errors.at(0));
                errorMessage.justifyCenter(centerX, centerY, 0, 40.f);
                errorMessage.draw(window);
            }
        }
        
        window.display();
    }
    
    return 0;
}
