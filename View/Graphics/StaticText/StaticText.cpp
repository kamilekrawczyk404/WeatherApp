//
// Created by Kamil Krawczyk on 27/04/2024.
//

#include "StaticText.h"

StaticText::StaticText(std::string content, int fontSize, sf::Color color) : CustomFont(), text(content, font, (int)fontSize), fontSize(fontSize){
    this->text.setFillColor(color);
    this->text.setFont(font);
}

void StaticText::draw(sf::RenderWindow &window) {
    window.draw(this->text);
}

void StaticText::setPosition(float x, float y) {
    this->text.setPosition(x, y);
}

void StaticText::setText(std::string& text) {
    this->text.setString(text);
}

void StaticText::justifyCenter(float centerX, float centerY, float offsetX, float offsetY) {
    this->setPosition(centerX - this->text.getLocalBounds().width / 2 + offsetX, centerY - this->text.getLocalBounds().height / 2 + offsetY);
}