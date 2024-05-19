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

nlohmann::json Helpers::getDate(time_t unixSeconds, int shift, int currentGMTOffset) {
    unixSeconds -= currentGMTOffset;
    unixSeconds += shift;
    
    tm* localTime = gmtime(&unixSeconds);
    int weekdayIndex = localTime->tm_wday,
        dayOfMonthIndex = localTime->tm_mday,
        monthIndex = localTime->tm_mon;
    

    const std::vector<std::string> 
            weekdaysInEnglish({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}),
            weekdaysInPolish({"Niedziela", "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota"}),
            monthsInEnglish({"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}),
            monthsInPolish({"Styczeń", "Luty", "Marzec", "Kwiecień", "Maj", "Czerwiec", "Lipiec", "Sierpień", "Wrzesień", "Październik", "Listopad", "Grudzień"});
    
    return nlohmann::json({
          {"english", weekdaysInEnglish[weekdayIndex] + ", " + std::to_string(dayOfMonthIndex) + " " + monthsInEnglish[monthIndex]}, 
          {"polish", weekdaysInPolish[weekdayIndex] + ", " + std::to_string(dayOfMonthIndex) + " " + monthsInPolish[monthIndex]}
    });
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

nlohmann::json Helpers::translate(std::string text) {
    
    if (text == "Clouds") {
        return nlohmann::json ({{"english", text}, {"polish", "Pochmurnie"}});
    } else if (text == "Rain") {
        return nlohmann::json ({{"english", text}, {"polish", "Deszcz"}});
    } else if (text == "Snow") {
        return nlohmann::json ({{"english", text}, {"polish", "Śnieg"}});
    } else if (text == "Clear") {
        return nlohmann::json ({{"english", text}, {"polish", "Bezchmurnie"}});
    } else if (text == "Drizzle") {
        return nlohmann::json ({{"english", text}, {"polish", "Mżawka"}});
    } else if (text == "Thunderstorm") {
        return nlohmann::json ({{"english", text}, {"polish", "Burza"}});
    } else {
        return nlohmann::json ({{"english", text}, {"polish", text}});
    }
}

float Helpers::LagrangeBasis(const std::vector<float>& x, int i, double xPoint) {
    float result = 1.0f;
    
    for(size_t j = 0; j < x.size(); j++) {
        if (j != i) {
            result *= (xPoint - x[j]) / (x[i] - x[j]);
        } 
    }
    
    return result;
}

float Helpers::LagrangePolynomial(const std::vector<float>& x, const std::vector<float>& y, float xPoint) {
    float result = 0.0f;
    
    for(size_t i = 0; i < x.size(); i++) {
        result += y[i] * Helpers::LagrangeBasis(x, i, xPoint);
    }
    
    return result;
}

sf::Color Helpers::convertTemperatureToColor(float temp) {
    const int tMin = -80, tMax = 50;

    return sf::Color(Helpers::HSLtoRGB(360 - (temp - tMin) / (tMax - tMin) * 360, 1, 0.5));
}