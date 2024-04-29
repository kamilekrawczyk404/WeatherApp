//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Weather.h"

using json = nlohmann::json;

Weather::Weather(std::string& location): Location(location) {
    FetchAPI api(getUrl());
    HandleJson rawJson(api.fetchedData);
    
    for(auto item : rawJson.content["list"]) {
        json partial({
//             {"date", item["dt_txt"]},
             {"weekday", Helpers::getWeekday(item["dt_txt"])},
             {"temperature", json ({
               {"feels_like", std::to_string(Helpers::toCelsius(item["main"]["feels_like"]))},
               {"temp_min", std::to_string(Helpers::toCelsius(item["main"]["temp_min"]))},
               {"temp_max", std::to_string(Helpers::toCelsius(item["main"]["temp_max"]))},
               {"main", std::to_string(Helpers::toCelsius(item["main"]["temp"]))},
             })},
             {"specificInformation", json({
                 {"humidity", item["main"]["humidity"]}, 
                 {"pressure", item["main"]["pressure"]},
                 {"cloudiness", item["clouds"]["all"]},
                 {"wind", json({
                     {"speed", item["wind"]["speed"]},
                     {"deg", item["wind"]["deg"]}
                 })},
                 {"visibility", std::to_string(item["visibility"].get<double>() / 1000)},
                 {"fall", json({
                     {"rain", item["rain"]["3h"]},
                     {"snow", item["snow"]["3h"]},
                 })},
             })},
             {"weather", json({
                  {"icon", item["weather"][0]["icon"].get<std::string>() + ".png"},
                  {"info", item["weather"][0]["main"]},
                  {"description", item["weather"][0]["description"]}
             })},
             
        });
        weatherForecast.push_back(partial);
    }
    locationInfo.push_back( {
        {"sunrise", Helpers::convertToClockFormat(rawJson.content["city"]["sunrise"].get<time_t>())},
        {"sunset", Helpers::convertToClockFormat(rawJson.content["city"]["sunset"].get<time_t>())},
        {"city", rawJson.content["city"]["name"].get<std::string>() + "," + rawJson.content["city"]["country"].get<std::string>()}
    });
    
//    std::cout << weatherForecast << std::endl;
}


std::string Weather::getUrl() {
    std::string url = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(this->lat) + "&lon=" + std::to_string(this->lon) + "&appid=" + WEATHER_API_KEY;
    
    return url;
}
