//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Location.h"

Location::Location(std::string name) : name(name) {
    FetchAPI api(getUrl());
    HandleJson json(api.fetchedData);
    
    this->lat = json.content["results"][0]["geometry"]["location"]["lat"].get<double>();
    this->lon = json.content["results"][0]["geometry"]["location"]["lng"].get<double>();
    
    std::cout << this->lat << std::endl;
}

Location::~Location() {
    std::cout << "Destructor..." << std::endl;
}

std::string Location::getUrl() {
    std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address=" + this->name + "&key=" + this->API_KEY;
    
    return url;
}
