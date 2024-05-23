//
// Created by Kamil Krawczyk on 25/04/2024.
//

#include "Weather.h"

using json = nlohmann::json;

json Weather::formatData(json &content, json &item) {
    json partial({
         {"partOfDay", item["sys"]["pod"]},
         {"hour", Helpers::getHourFromUnix(item["dt"].get<time_t>(), (content["city"]["timezone"].get<int>()))},
         {"weekday", Helpers::getDate(item["dt"].get<time_t>(), (content["city"]["timezone"].get<int>()))},
         {"temperature", json ({
            {"feelsLike", std::to_string(Helpers::toCelsius(item["main"]["feels_like"]))},
            {"tempMin", std::to_string(Helpers::toCelsius(item["main"]["temp_min"]))},
            {"tempMax", std::to_string(Helpers::toCelsius(item["main"]["temp_max"]))},
            {"main", std::to_string(Helpers::toCelsius(item["main"]["temp"]))},
         })},
         {"specificInformation", json({
            {"Humidity", json({
                {"title", json({{"english", "Humidity"}, {"polish", "Wilgotność"}})},
                {"value", std::to_string(item["main"]["humidity"].get<int>()) + "%"}
            })},
            {"Pressure", json({
                {"title", json({{"english", "Air pressure"}, {"polish", "Ciśnienie"}})},
                {"value", std::to_string(item["main"]["grnd_level"].get<int>()) + "hPa"}
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
            {"description", Helpers::translate(item["weather"][0]["description"])},
            {"precipitation", Helpers::removeDecimalZeros(item["pop"].get<float>() * 100) + "%"},
            {"fall", item.contains("rain") ? (std::to_string(item["rain"]["3h"].get<int>()) + " mm/3h") : (item.contains("snow") ? std::to_string(item["snow"]["3h"].get<int>()) + " mm/3h" : "")}
        })},
    });

    descriptions.push_back(item["weather"][0]["description"]);
    
    return partial;
}

Weather::Weather(std::string& location, std::vector<std::string> &countries): 
    Location(location), 
    LocationImage(location),
    countries(countries) {
    try {
        FetchAPI api(getUrl());
        bool
            newDay = true;
        int
            length = api.fetchedData["list"].size(),
            currentDay = 0,
            minIndex = -1,
            maxIndex = -1,
            index = 0;
        float
            minDuringDay,
            maxDuringDay,
            currentMax,
            currentMin,
            lowest,
            highest;

        json singleDay;

        for (auto& [key, item] : api.fetchedData["list"].items()) {
            json  partial = Weather::formatData(api.fetchedData, item);
            singleDay.push_back(partial);

            currentMax = std::max(item["main"]["temp_max"].get<float>(), item["main"]["temp_min"].get<float>());
            currentMin = std::min(item["main"]["temp_max"].get<float>(), item["main"]["temp_min"].get<float>());

            if (newDay) {
                minDuringDay = currentMin;
                maxDuringDay = currentMax;
                maxIndex = minIndex = index;
                newDay = false;
            }

            if (!stoi(key)) {
                highest = currentMax;
                lowest = currentMin;
            }

            if (highest < currentMax) {
                highest = currentMax;
            } else if (lowest > currentMin) {
                lowest = currentMin;
            }

            if (currentMax >= maxDuringDay) {
                maxDuringDay = currentMax;
                maxIndex = index;
            } else if (currentMin <= minDuringDay) {
                minDuringDay = currentMin;
                minIndex = index;
            }

            // next iteration is next day
            if (stoi(key) + 1 != length && partial["weekday"] != Helpers::getDate(api.fetchedData["list"][stoi(key) +  1]["dt"].get<time_t >(), api.fetchedData["city"]["timezone"].get<int>())) {

                // to prevent situation that first day has lack of information take them from the next day
                const int infoPacketsPerDay = 8;
                int startingFrom = singleDay.size();

                if (startingFrom < infoPacketsPerDay) {
                    while (startingFrom < infoPacketsPerDay) {
                        partial = Weather::formatData(api.fetchedData, api.fetchedData["list"][startingFrom]);

                        float
                                nextMaxTemp = api.fetchedData["list"][startingFrom]["main"]["temp_max"].get<float>(),
                                nextMinTemp = api.fetchedData["list"][startingFrom]["main"]["temp_min"].get<float>();

                        if (currentMax < nextMaxTemp) {
                            maxDuringDay = nextMaxTemp;
                            maxIndex = startingFrom;
                        } else if (currentMin > nextMinTemp) {
                            minDuringDay = nextMinTemp;
                            minIndex = startingFrom;
                        }

                        singleDay.push_back(partial);
                        startingFrom++;
                    }
                }

                weatherForecast.push_back({
                   {"data", singleDay},
                   // if condition is true, both temperatures are equal
                   {"max", maxIndex == -1 ? minIndex : maxIndex},
                   {"min", minIndex == -1 ? maxIndex : minIndex}
                });

                currentDay++;
                newDay = true;
                singleDay = {};
                index = 0;
                maxIndex = minIndex = -1;

                continue;
            }
            index++;
        }
        
        nlohmann::json descriptionsAsJson = descriptions;

        int j = 0;
        while(j < countries.size()) {
            std::string lang = countries[j++];

            // skip getting translations from english, because weather api already responds data in that language
            if (lang != "en") {
                TranslationAPI translationApi(descriptionsAsJson, lang);
                translatedDescriptions.push_back({{lang, translationApi.fetchedData}});
            } else {
                // description in english still includes spaces, replace them using the new line character
                for (auto &item : descriptionsAsJson) {
                    std::string text = item;
                    std::replace(text.begin(), text.end(), ' ', '\n');
                    item = text;
                }
                translatedDescriptions.push_back({{lang, descriptionsAsJson}});
            }
        }
        
        for (auto &[singleDayKey, singleDay] : weatherForecast.items()) {
            for (auto &[hourlyKey, item] : singleDay["data"].items()) {
                nlohmann::json newDescription;
                int countryIndex = 0;
                
                // old description need to replaced with translated values
                for (std::string country : countries) {
                    newDescription.push_back(nlohmann::json ({{country, translatedDescriptions[countryIndex++][country][stoi(singleDayKey) * singleDay["data"].size() + stoi(hourlyKey)]}}));
                }
                
                item["weather"]["description"] = newDescription;
            }
        }
        
        additionalInfo = {
            {"sunrise", Helpers::convertToClockFormat(api.fetchedData["city"]["sunrise"].get<time_t>(), api.fetchedData["city"]["timezone"].get<int>())},
            {"sunset", Helpers::convertToClockFormat(api.fetchedData["city"]["sunset"].get<time_t>(), api.fetchedData["city"]["timezone"].get<int>())},
            {"city", api.fetchedData["city"]["name"].get<std::string>() + ", " + api.fetchedData["city"]["country"].get<std::string>()},
            {"timezone", api.fetchedData["city"]["timezone"].get<int>()},
            {"lowestTemp", std::to_string(Helpers::toCelsius(lowest))},
            {"highestTemp", std::to_string(Helpers::toCelsius(highest))}
        };
    } catch(std::string &error) {
        std::cerr << error << std::endl;
    }
}

std::string Weather::getUrl() {
    std::string url = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(this->lat) + "&lon=" + std::to_string(this->lon) + "&appid=" + WEATHER_API_KEY;
    
    return url;
}
