//
// Created by Kamil Krawczyk on 27/04/2024.
//

#include "CustomFont.h"

CustomFont::CustomFont(std::string filepath) {
    if (!this->font.loadFromFile(filepath)) {
        std::cerr << "Failed to load font package" << std::endl;
    }
    this->font.setSmooth(true);
}