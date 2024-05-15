//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Weather.h"

using json = nlohmann::json;

Weather::Weather(std::string& location): Location(location), LocationImage(location) {
    FetchAPI api(getUrl());
    HandleJson rawJson(api.fetchedData);
    
    bool isDay, newDay;
    int length = rawJson.content["list"].size(), currentDay = 0;
    float min, max, currentTemp;
    std::string  highestTemp = "null", lowestTemp = "null";
    json weekdayForecast {
        {"day", ""},
        {"night", ""}
    };;
    
    for (auto& [key, item] : rawJson.content["list"].items()) {
        isDay = false;
        if (item["sys"]["pod"] == "d") {
            isDay = true;
        }
        
        json partial({
            {"hour", Helpers::getHourFromUnix(item["dt"].get<time_t>(), (rawJson.content["city"]["timezone"].get<int>()))},
            {"weekday", Helpers::getDate(item["dt"].get<time_t>(), (rawJson.content["city"]["timezone"].get<int>()))},
            {"temperature", json ({
                {"feels_like", std::to_string(Helpers::toCelsius(item["main"]["feels_like"]))},
                {"temp_min", std::to_string(Helpers::toCelsius(item["main"]["temp_min"]))},
                {"temp_max", std::to_string(Helpers::toCelsius(item["main"]["temp_max"]))},
                {"main", std::to_string(Helpers::toCelsius(item["main"]["temp"]))},
            })},
            {"specificInformation", json({
                {"Humidity", json({
                    {"title", json({{"english", "Humidity"}, {"polish", "Wilgotność"}})},
                    {"value", std::to_string(item["main"]["humidity"].get<int>()) + "%"}
                })},
                {"Pressure", json({
                    {"title", json({{"english", "Air pressure"}, {"polish", "Ciśnienie"}})},
                    {"value", std::to_string(item["main"]["pressure"].get<int>()) + "hPa"}
                })},
                {"Cloudiness", json({
                    {"title", json({{"english", "Cloudiness"}, {"polish", "Zachmurzenie"}})},
                    {"value", std::to_string(item["clouds"]["all"].get<int>()) + "%"}
                })},
                {"Wind", json({
                    {"title", json({{"english", "Wind"}, {"polish", "Wiatr"}})},
                    {"value", Helpers::removeDecimalZeros<float>(item["wind"]["speed"].get<float>()) + "m/s"},
                    {"deg", item["wind"]["deg"].get<float>()}
                })},
                {"Visibility", json({
                    {"title", json({{"english", "Visibility"}, {"polish", "Widoczność"}})},
                    {"value", item.contains("visibility") ? (std::to_string(item["visibility"].get<int>() / 1000)  + "km") : "No data"}
                })},
            })},
            {"weather", json({
                {"icon", item["weather"][0]["icon"].get<std::string>() + ".png"},
                {"info", Helpers::translate(item["weather"][0]["main"].get<std::string>())},
                {"description", item["weather"][0]["description"]}
            })}
        });
        
        if (newDay) {
            min = item["main"]["temp_min"].get<float>();
            max = item["main"]["temp_max"].get<float>();
            
            weekdayForecast["night"] = partial;
            newDay = false;
        }
        
        if (isDay) {
            currentTemp = std::max(item["main"]["temp_max"].get<float>(), item["main"]["temp_min"].get<float>());
            if (currentTemp > max) {
                weekdayForecast["day"] = partial;
                max = currentTemp;
            }
        } else {
            currentTemp = std::min(item["main"]["temp_max"].get<float>(), item["main"]["temp_min"].get<float>());
            if (min < currentTemp) {
                weekdayForecast["night"] = partial;
                min = currentTemp;
            }
        }
        
        // next iteration is next day
        if (stoi(key) + 1 != length && partial["weekday"] != Helpers::getDate(rawJson.content["list"][stoi(key) +  1]["dt"].get<time_t >(), rawJson.content["city"]["timezone"].get<int>())) {
            // remove unnecessary properties
            if (weekdayForecast["day"] == "") {
                weekdayForecast.erase("day");
            }
            if (weekdayForecast["night"] == "") {
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
    
    // getting the highest and the lowest temperature during the day
    for (auto& [key, value] : weatherForecast.items()) {
        if (value.contains("day")) {
            std::string current = value["day"]["temperature"]["temp_max"].get<std::string>();

            if (highestTemp == "null") {
                highestTemp = current;
            } else {
                highestTemp = (stoi(highestTemp) < stoi(current)) ? current : highestTemp; 
            }
        } 
        if (value.contains("night")){
            std::string current = value["night"]["temperature"]["temp_min"].get<std::string>();

            if (lowestTemp == "null") {
                lowestTemp = current;
            } else {
                lowestTemp = (stoi(lowestTemp) > stoi(current)) ? current : lowestTemp;
            }
        }
    }

    additionalInfo.push_back( {
      {"sunrise", Helpers::convertToClockFormat(rawJson.content["city"]["sunrise"].get<time_t>(), rawJson.content["city"]["timezone"].get<int>())},
      {"sunset", Helpers::convertToClockFormat(rawJson.content["city"]["sunset"].get<time_t>(), rawJson.content["city"]["timezone"].get<int>())},
      {"city", rawJson.content["city"]["name"].get<std::string>() + ", " + rawJson.content["city"]["country"].get<std::string>()},
      {"timezone", rawJson.content["city"]["timezone"].get<int>()},
      {"lowestTemp", stoi(lowestTemp)},
      {"highestTemp", stoi(highestTemp)}
    });
}

std::string Weather::getUrl() {
    std::string url = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(this->lat) + "&lon=" + std::to_string(this->lon) + "&appid=" + WEATHER_API_KEY;
    
    return url;
}
