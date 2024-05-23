//
// Created by Kamil Krawczyk on 22/05/2024.
//

#ifndef CPP_WEATHER_APP_TRANSLATIONAPI_H
#define CPP_WEATHER_APP_TRANSLATIONAPI_H

#include "FetchAPI.h"
#include "KEYS.h"
#include <string>
#include <vector>

class TranslationAPI : public FetchAPI {
public:
    TranslationAPI(nlohmann::json &values, std::string targetLanguage);
    
};


#endif //CPP_WEATHER_APP_TRANSLATIONAPI_H
