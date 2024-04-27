//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Location.h"

Location::Location(std::string& name, std::vector<std::string>& errors) : name(name) {
    try {
        std::cout << name << std::endl;
        
        FetchAPI api(getUrl());

        HandleJson json(api.fetchedData);

        this->lat = json.content["results"][0]["geometry"]["location"]["lat"].get<double>();
        this->lon = json.content["results"][0]["geometry"]["location"]["lng"].get<double>();
    } catch (const std::runtime_error& e) {
        errors[0] = "Our system can't find provided city";
    }
    
    
    
}

std::string Location::getUrl() {
    std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address=" + this->name + "&key=" + GOOGLE_LOCATION_API_KEY;
    
    return url;
}
