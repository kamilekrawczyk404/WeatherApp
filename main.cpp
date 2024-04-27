#include <SFML/Graphics.hpp>
#include "Backend/Weather.h"
#include "Graphics/Inputs/Input.h"
#include "Graphics/StaticText/StaticText.h"
#include <vector>

std::vector<std::string> errors = {""};

void getLocation(std::string content) {
    Weather weather(content, errors);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Simple Forecast Application");
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;
    
    Input locationInput(300.f, 30.f, getLocation, 14.f, "Enter your location...");
    locationInput.setPosition((centerX - locationInput.background.getSize().x / 2), (centerY - locationInput.background.getSize().y / 2));
    
    StaticText title("Weather Forecast Application", 20, sf::Color::White);
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
        
        locationInput.draw(window);
        title.draw(window);

        if (errors.size()) {
            errorMessage.setText(errors.at(0));
            errorMessage.justifyCenter(centerX, centerY, 0, 40.f);
            errorMessage.draw(window);
        }
        window.display();
    }
    
    return 0;
}
