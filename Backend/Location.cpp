//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Location.h"

Location::Location(std::string& name) {
    // replace any spaces
    for(char& c : name) {
        if (c == ' ') {
            c = '+';
        }
    }
    this->name = name;
    FetchAPI api(getUrl());
    
    if (!api.errorMessage.empty()) {
       this->errorMessage = api.errorMessage;
    } else {
        HandleJson json(api.fetchedData);

        this->lat = json.content["results"][0]["geometry"]["location"]["lat"].get<double>();
        this->lon = json.content["results"][0]["geometry"]["location"]["lng"].get<double>();
    }
}

std::string Location::getUrl() {
    std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address=" + this->name + "&key=" + GOOGLE_API_KEY;
    
    return url;
}

bool Location::isOk() {
    return this->errorMessage.empty();
}
