//
// Created by Kamil Krawczyk on 29/04/2024.
//

#ifndef CPP_WEATHER_APP_HELPERS_H
#define CPP_WEATHER_APP_HELPERS_H

#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "FetchAPI.h"
#include "KEYS.h"
#include <curl/curl.h>
#include <filesystem>


class Helpers {
public:
    static int toCelsius(const double kelvins, int digits = 10);
    static int getHourFromUnix(time_t unixSeconds, int shift, int currentGMTOffset = 7200);
    static std::string convertToClockFormat(time_t unix, int shift = 0,  int currentGMTOffset = 7200);
    static nlohmann::json getDate(time_t unixSeconds, int shift = 0, int currentGMTOffset = 7200);
    static sf::Color HSLtoRGB(float hue, float saturation, float lightness);
    static float LagrangeBasis(const std::vector<float>& x, int i, double xPoint);
    static float LagrangePolynomial(const std::vector<float>& x, const std::vector<float>& y, float xPoint);
    static sf::Color convertTemperatureToColor(float temp);
    static std::string urlEncode(const std::string &value);
    static std::string getPath(std::string path = "");
    
    template<typename T>
    static int findIndex(std::vector<T> &array, T &seeking) {
        int i = 0;
        for (T item : array) {
            if (item == seeking)
                return i;
            i++;
        }
        return -1;
    }

    template<typename T>
    static std::vector<T> removeDuplicates(std::vector<T> &array) {
        std::vector<T> newArray;

        for(T element : array) {
            bool contains = false;
            for (int i = 0; i < newArray.size(); i++) {
                if (!contains) {
                    contains = newArray[i] == element;
                    continue;
                }
                break;
            }

            if (!contains) {
                newArray.push_back(element);
            }
        }

        return newArray;
    }

    template<typename T>
    static std::string removeDecimalZeros(T number, int precision = 2) {
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(precision) << number;

        return oss.str();
    };
};


#endif //CPP_WEATHER_APP_HELPERS_H
