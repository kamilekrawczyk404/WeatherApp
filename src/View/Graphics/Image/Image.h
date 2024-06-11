//
// Created by Kamil Krawczyk on 28/04/2024.
//

#ifndef CPP_WEATHER_APP_IMAGE_H
#define CPP_WEATHER_APP_IMAGE_H
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class Image {
public:
    sf::Sprite image;
    sf::Texture texture;
    sf::Vector2u textureSize;
    Image(std::string path);
    void draw(sf::RenderWindow& window);
    void load(std::string path);
};


#endif //CPP_WEATHER_APP_IMAGE_H
