//
// Created by Kamil Krawczyk on 28/04/2024.
//

#include "Image.h"

Image::Image(std::string path) {
    if (!this->texture.loadFromFile(path)) {
        std::cerr << "Failed to load image" << std::endl;
    } else {
        this->textureSize = this->texture.getSize();
        
        this->texture.setSmooth(true);
        this->image.setTexture(texture);
    }
}

void Image::draw(sf::RenderWindow& window) {
    window.draw(this->image);
}