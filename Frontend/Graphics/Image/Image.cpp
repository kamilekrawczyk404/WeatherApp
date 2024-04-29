//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Image.h"

Image::Image(std::string path) {
    if (!this->texture.loadFromFile(path)) {
        std::cerr << "Failed to load image" << std::endl;
    } else {
        this->textureSize = this->texture.getSize();
        
//        this->texture.setSmooth(true);
        this->image.setTexture(texture);
//        this->image.s
//        this->image.setPosition(10.f, 10.f);
//        this->image.setTextureRect(sf::IntRect(100, 100, 100, 100));

//        this->image.setOrigin((float)this->texture.getSize().x / 2, (float)this->texture.getSize().y / 2);
//        this->image.rotate(180.f);
//        this->image.setScale(1.5f, 1.5f);
    }
}

void Image::draw(sf::RenderWindow& window) {
//    this->texture.update(window);
    window.draw(this->image);
}