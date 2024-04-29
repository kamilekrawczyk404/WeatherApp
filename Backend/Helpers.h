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


class Helpers {
public:
    static int toCelsius(const double kelvins, int digits = 10);
    static std::string replaceAll(std::string str, const std::string from, const std::string to);
    static std::string convertToClockFormat(const time_t unix);
    static std::string getWeekday(const std::string date);
};


#endif //CPP_WEATHER_APP_HELPERS_H
