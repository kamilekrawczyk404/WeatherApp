//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "CelsiusSign.h"

CelsiusSign::CelsiusSign(sf::RenderWindow& window, float x, float y, int fontSize, std::string temperature) {
    StaticText degreeSymbol("o", fontSize / 2);
    StaticText cSymbol("C", fontSize);
    
    int length = temperature[0] == '-' ? temperature.substr(1, temperature.length()).length() : temperature.length();
    
    degreeSymbol.setPosition(x + length * (fontSize / 1.75f) + fontSize / 8, y + 2.f);
    cSymbol.setPosition(x + length * (fontSize / 1.75f) + degreeSymbol.text.getLocalBounds().width + fontSize / 4, y);
    
    cSymbol.draw(window);
    degreeSymbol.draw(window);
}