//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "CelsiusSign.h"

CelsiusSign::CelsiusSign(sf::RenderWindow& window, int fontSize, sf::Text &temperature) {
    StaticText degreeSymbol("o", fontSize / 2);
    StaticText cSymbol("C", fontSize);
    
    degreeSymbol.text.setPosition(temperature.getPosition().x + temperature.getGlobalBounds().width + fontSize / 5, temperature.getPosition().y);
    degreeSymbol.draw(window);
    
    cSymbol.text.setPosition(degreeSymbol.text.getPosition().x + degreeSymbol.text.getGlobalBounds().width, degreeSymbol.text.getPosition().y);
    cSymbol.draw(window);
}