//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "CelsiusSign.h"

CelsiusSign::CelsiusSign(sf::RenderWindow& window, int fontSize, sf::Text &temperature) {
    StaticText degreeSymbol("o", fontSize / 2);
    StaticText cSymbol("C", fontSize);
    
    degreeSymbol.setPosition(fontSize / 5 + temperature.getPosition().x + temperature.getLocalBounds().width, temperature.getPosition().y);
    degreeSymbol.draw(window);
    
    cSymbol.setPosition(degreeSymbol.text.getPosition().x + degreeSymbol.text.getGlobalBounds().width, temperature.getPosition().y);
    cSymbol.draw(window);
    
}