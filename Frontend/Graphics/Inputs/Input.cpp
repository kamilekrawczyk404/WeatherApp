//
// Created by Kamil Krawczyk on 27/04/2024.
//

#include "Input.h"

Input::Input(float width, float height, fncPtr func, float fontSize, std::string placeholder) : onEnterHandler(func), placeholder(placeholder), fontSize(fontSize), width(width), height(height), customFont(), background(sf::Vector2<float>(width, height)), inputText("", customFont.font, (int)fontSize) {
    this->background.setFillColor(sf::Color(255, 255, 255, 255 / 2));
    this->background.setOutlineColor(sf::Color(32, 32, 32));
    this->background.setOutlineThickness(2.f);
    
    this->inputText.setFillColor(sf::Color(32, 32, 32));
    
    if (this->placeholder.length()) {
        this->setPlaceholder();
    }
}

void Input::setPlaceholder() {
    this->inputText.setString(placeholder);
}

void Input::setPosition(float x, float y) {
    this->background.setPosition(x, y);
    this->inputText.setPosition(x + 10.f, (y + height / 2 - this->fontSize / 2));
}

void Input::textEntered(sf::Event& event, std::vector<std::string>& errors) {
    errors[0] = "";
    
    if (event.text.unicode < 128) {
        if (this->inputText.getString() == placeholder && event.text.unicode != '\b') {
            this->inputText.setString("");
        }
        
        if (event.text.unicode == '\b' && !this->inputText.getString().isEmpty() && this->inputText.getString() != placeholder) {
            this->inputText.setString(this->inputText.getString().substring(0, this->inputText.getString().getSize() - 1));
        } else if (event.text.unicode != '\b' && (int)this->inputText.getString().getSize() <= (int)width / 10 && event.key.code != 10 ) {
            this->inputText.setString(this->inputText.getString() + static_cast<char>(event.text.unicode));

        } else if (event.key.code == 10) {
            if (this->inputText.getString().isEmpty()) {
                // user hasn't entered any text, set error flag - empty content
                errors[0] = "You haven't entered any information!";
            } else {
                // call method
                this->onEnter();
            } 
        }
    }
}

void Input::draw(sf::RenderWindow& window) {
    window.draw(this->background);
    window.draw(this->inputText);
}

void Input::onEnter() {
    onEnterHandler(this->inputText.getString());
//    std::cout << content << std::endl;
}





