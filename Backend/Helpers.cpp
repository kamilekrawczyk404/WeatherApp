//
// Created by Kamil Krawczyk on 29/04/2024.
//

#include "Helpers.h"

int Helpers::toCelsius(const double kelvins, int digits) {
    if (digits == 0)
        return 0;
    return round((kelvins - 273.15));
}

std::string Helpers::convertToClockFormat(time_t unix, int shift,  int currentGMTOffset) {
    unix -= currentGMTOffset;
    unix += shift;
    
    struct tm * timeinfo;
    timeinfo = localtime(&unix);
    char buffer[6];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

    return buffer;
}

std::string Helpers::getWeekday(time_t unixSeconds, int shift, int currentGMTOffset) {
    unixSeconds -= currentGMTOffset;
    unixSeconds += shift;
    
    tm* localTime = gmtime(&unixSeconds);
    int weekdayIndex = localTime->tm_wday;

    const std::vector<std::string> weekdays({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"});
    
    return weekdays[weekdayIndex];
}

int Helpers::getCurrentHour(int shift, int currentGMTOffset) {
    auto now = std::chrono::system_clock::now();
    auto nowC = std::chrono::system_clock::to_time_t(now);
    nowC -= currentGMTOffset;
    nowC += shift;
    
    std::tm *localTime = std::localtime(&nowC);
    int currentHour = localTime->tm_hour;

    return currentHour;
}

int Helpers::getHourFromUnix(time_t unixSeconds, int shift, int currentGMTOffset) {
    unixSeconds -= currentGMTOffset;
    unixSeconds += shift;
    
    tm* localTime = gmtime(&unixSeconds);
    int hour = localTime->tm_hour;
    
    return hour;
}



sf::Color Helpers::HSLtoRGB(float hue, float saturation, float lightness) {
    float c = (1 - std::abs(2 * lightness - 1)) * saturation;
    float x = c * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
    float m = lightness - c / 2;

    float r, g, b;

    if (0 <= hue && hue < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (60 <= hue && hue < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (120 <= hue && hue < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (180 <= hue && hue < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (240 <= hue && hue < 300) {
        r = x;
        g = 0;
        b = c;
    } else { // 300 <= hue && hue < 360
        r = c;
        g = 0;
        b = x;
    }

    return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}
