//
// Created by Kamil Krawczyk on 26/04/2024.
//

#include "HandleJson.h"

HandleJson::HandleJson(std::string rawJson) {
    this->content = json::parse(rawJson);
}

HandleJson::~HandleJson() {
    std::cout << "Destructor.." << std::endl;
}