//
// Created by Kamil Krawczyk on 09/06/2024.
//

#include "SuggestLocation.h"

SuggestLocation::SuggestLocation(std::string &locationPrefix) : FetchAPI("https://maps.googleapis.com/maps/api/place/autocomplete/json?input=" + locationPrefix + "&key=" + GOOGLE_API_KEY) {
}