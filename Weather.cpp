//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Weather.h"

using json = nlohmann::json;

Weather::Weather(std::string location): Location(location) {
    FetchAPI api(getUrl());
    HandleJson rawJson(api.fetchedData);

    for(auto item : rawJson.content["list"]) {
        json partial({
             {"date", item["dt_txt"] },
             {"temperature", json ({
               {"feels_like", toCelsius<double>(item["main"]["feels_like"].get<double>())},
               {"temp_min", toCelsius<double>(item["main"]["temp_min"])},
               {"temp_max", toCelsius<double>(item["main"]["temp_max"])},
               {"main", toCelsius<double>(item["main"]["temp"])},
             })},
             {"humidity", item["main"]["humidity"]},
             {"pressure", item["main"]["pressure"]},
             {"weather", json({
                  {"info", item["weather"][0]["main"]},
                  {"description", item["weather"][0]["description"]}
             })},
             {"cloudiness", item["clouds"]["all"]},
             {"wind", json({
                   {"speed", item["wind"]["speed"]},
                   {"deg", item["wind"]["deg"]}
             })},
              {"visibility", item["visibility"].get<double>() / 1000},
              {"fall", json({
                  "rain", item["rain"]["3h"],
                  "snow", item["snow"]["3h"]
              })},
        });
        
        weatherForecast.push_back(partial);
        weatherForecast.push_back(json({
            {"sunrise", convertToHoursAndSeconds(rawJson.content["city"]["sunrise"].get<time_t>())},
            {"sunset", convertToHoursAndSeconds(rawJson.content["city"]["sunset"].get<time_t>())},
        }));
    }
}

Weather::~Weather() {
    std::cout << "Destructor..." << std::endl;
}

std::string Weather::getUrl() {
    std::string url = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(this->lat) + "&lon=" + std::to_string(this->lon) + "&appid=" + this->API_KEY;
    
    return url;
}

template<typename T>
double Weather::toCelsius(T kelvins, int digits) {
    return round((kelvins - 273.15) * digits) / digits;
}

std::string Weather::convertToHoursAndSeconds(time_t unix) {
    struct tm * timeinfo;
    timeinfo = localtime(&unix);
    char buffer[6];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    
    return buffer;
}