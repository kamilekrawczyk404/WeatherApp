//
// Created by Kamil Krawczyk on 27/04/2024.
//

#include "Input.h"

Input::Input(float width, float height, fncPtr func, float fontSize, std::string placeholder) : onEnterHandler(func), placeholder(placeholder), fontSize(fontSize), width(width), height(height), customFont(), background(sf::Vector2<float>(width, height)), inputText("", customFont.font, (int)fontSize) {
    this->background.setFillColor(sf::Color::White);
    this->background.setOutlineColor(sf::Color::Black);
    this->background.setOutlineThickness(2.f);
    
    this->inputText.setFillColor(sf::Color::Black);
    
    if (this->placeholder.length()) {
        this->inputText.setString(this->placeholder);
    }
}

void Input::setPosition(float x, float y) {
    this->background.setPosition(x, y);
    this->inputText.setPosition(x + 10.f, (y + height / 2 - this->fontSize / 2));
}

void Input::checkOverflow(bool ltr) {
    float static margin = 0;
    float textWidth = this->inputText.getLocalBounds().width;
    float backgroundWidth = this->background.getSize().x;

    // 10.f - little padding from the right side
    if (textWidth + 20.f > backgroundWidth)  {
        if (!ltr) {
            // translate axis to the left if the text inside input is greater than background's width
            margin += 8.f;
        } else {
            // translate axis to the right when user erases text
            margin -= 8.f;
        }
        this->inputText.setPosition(this->background.getPosition().x + 10.f + margin, this->background.getPosition().y + (height / 3.f) );
    }
}

void Input::textEntered(sf::Event& event, std::vector<std::string>& errors) {
    errors[0] = "";
    
    if (this->inputText.getString() == this->placeholder) {
        this->inputText.setString("");
    }
    
    if (event.text.unicode < 128) {
        if (event.text.unicode == '\b' && !this->inputText.getString().isEmpty()) {
            this->inputText.setString(this->inputText.getString().substring(0, this->inputText.getString().getSize() - 1));
            
            checkOverflow(false);
            
        } else if (event.text.unicode != '\b' && event.key.code != 10) {
            this->inputText.setString(this->inputText.getString() + static_cast<char>(event.text.unicode));

            checkOverflow();
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





