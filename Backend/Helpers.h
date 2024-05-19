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

class Helpers {
public:
    template<typename T>
    static std::string removeDecimalZeros(T number, int precision = 2) {
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(precision) << number;

        return oss.str();
    };
    
    // currentGMTOffset- current user time zone
    static int toCelsius(const double kelvins, int digits = 10);
    static int getHourFromUnix(time_t unixSeconds, int shift, int currentGMTOffset = 7200);
    static std::string convertToClockFormat(time_t unix, int shift = 0,  int currentGMTOffset = 7200);
    static nlohmann::json getDate(time_t unixSeconds, int shift, int currentGMTOffset = 7200);
    static int getCurrentHour(int shift = 0, int currentGMTOffset = 7200);
    static sf::Color HSLtoRGB(float hue, float saturation, float lightness);
    static nlohmann::json translate(std::string text);
    static float LagrangeBasis(const std::vector<float>& x, int i, double xPoint);
    static float LagrangePolynomial(const std::vector<float>& x, const std::vector<float>& y, float xPoint);
    static sf::Color convertTemperatureToColor(float temp);
};


#endif //CPP_WEATHER_APP_HELPERS_H
