//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Weather.h"

using json = nlohmann::json;

Weather::Weather(std::string& location): Location(location) {
    FetchAPI api(getUrl());
    HandleJson rawJson(api.fetchedData);
    
    // has day and night flags
    bool isDay, newDay;
    // count of weather information with 3h interval
    int length = rawJson.content["list"].size(), hour, currentDay = 0;
    float min, max, currentTemp;
    std::string currentDate;
    json weekdayForecast;
    
    for (auto& [key, item] : rawJson.content["list"].items()) {
        isDay = false;
        hour = stoi(item["dt_txt"].get<std::string>().substr(11, 13));
        // substring for getting only date
        currentDate = item["dt_txt"].get<std::string>().substr(0, 10);

        if (hour >= 6 && hour <= 21) {
            isDay = true;
        }
        
        json partial({
            {"hour", stoi(item["dt_txt"].get<std::string>().substr(11,13))},
            {"weekday", Helpers::getWeekday(item["dt_txt"])},
            {"temperature", json ({
                {"feels_like", std::to_string(Helpers::toCelsius(item["main"]["feels_like"]))},
                {"temp_min", std::to_string(Helpers::toCelsius(item["main"]["temp_min"]))},
                {"temp_max", std::to_string(Helpers::toCelsius(item["main"]["temp_max"]))},
                {"main", std::to_string(Helpers::toCelsius(item["main"]["temp"]))},
            })},
            {"specificInformation", json({
                {"Humidity", json({
                    {"title", "Humidity"},
                    {"value", std::to_string(item["main"]["humidity"].get<int>()) + "%"}
                })},
                {"Pressure", json({
                    {"title", "Air Pressure"},
                    {"value", std::to_string(item["main"]["pressure"].get<int>()) + "PS"}
                })},
                {"Cloudiness", json({
                    {"title", "Cloudiness"},
                    {"value", std::to_string(item["clouds"]["all"].get<int>()) + "%"}
                })},
                {"Wind", json({
                    {"title", "Wind speed"},
                    {"value", Helpers::removeDecimalZeros<float>(item["wind"]["speed"].get<float>()) + "m/s"},
                    {"deg", item["wind"]["deg"].get<float>()}
                })},
                {"Visibility", json({
                    {"title", "Visibility"},
                    {"value", item.contains("visibility") ? (std::to_string(item["visibility"].get<int>() / 1000)  + "km") : "No data"}
                })},
            })},
            {"weather", json({
                {"icon", item["weather"][0]["icon"].get<std::string>().substr(0, 2) + (isDay ? "d" : "n")  + ".png"},
                {"info", item["weather"][0]["main"]},
                {"description", item["weather"][0]["description"]}
            })}
        });
        
        if (stoi(key) == 0) {
            // current weather
            weekdayForecast[isDay ? "day" : "night"] = partial;
        } else if (currentDay != 0) {
            if (newDay) {
                min = item["main"]["temp_min"].get<float>();
                max = item["main"]["temp_max"].get<float>();
                weekdayForecast["night"] = partial;
                newDay = false;
                continue;
            }
            if (isDay) {
                currentTemp = item["main"]["temp_max"].get<float>();
                if (currentTemp > max) {
                    weekdayForecast["day"] = partial;
                    max = currentTemp;
                }
            } else {
                currentTemp = item["main"]["temp_min"].get<float>();
                if (min < currentTemp) {
                    weekdayForecast["night"] = partial;
                    min = currentTemp;
                }
            }
        }
        
        
        if (stoi(key) + 1 != length && currentDate != rawJson.content["list"].at(stoi(key) + 1)["dt_txt"].get<std::string>().substr(0, 10)) {
            // next iteration is next day
            
            // remove unnecessary properties
            if (weekdayForecast["day"].empty()) {
                weekdayForecast.erase("day");
            } else if (weekdayForecast["night"].empty()) {
                weekdayForecast.erase("night");
            }
            
            currentDay++;
            newDay = true;
            weatherForecast.push_back(weekdayForecast);
            weekdayForecast = {
                {"day", ""},
                {"night", ""}
            };
        }
    }
    
    locationInfo.push_back( {
        {"sunrise", Helpers::convertToClockFormat(rawJson.content["city"]["sunrise"].get<time_t>())},
        {"sunset", Helpers::convertToClockFormat(rawJson.content["city"]["sunset"].get<time_t>())},
        {"city", rawJson.content["city"]["name"].get<std::string>() + ", " + rawJson.content["city"]["country"].get<std::string>()}
    });
}

std::string Weather::getUrl() {
    std::string url = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(this->lat) + "&lon=" + std::to_string(this->lon) + "&appid=" + WEATHER_API_KEY;
    
    return url;
}
