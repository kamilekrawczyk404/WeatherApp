//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "CelsiusSign.h"

CelsiusSign::CelsiusSign(sf::RenderWindow& window, float x, float y, int fontSize ) {
    StaticText degreeSymbol("o", fontSize / 2, sf::Color::White);
    StaticText cSymbol("C", fontSize, sf::Color::White);
    
    degreeSymbol.setPosition(x, y + 2.f);
    cSymbol.setPosition(x + (float)fontSize / 3, y);
    
    cSymbol.draw(window);
    degreeSymbol.draw(window);
}