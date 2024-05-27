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
        weekdaysInGerman({"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"}),
        
        monthsInEnglish({"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}),
        monthsInPolish({"Styczeń", "Luty", "Marzec", "Kwiecień", "Maj", "Czerwiec", "Lipiec", "Sierpień", "Wrzesień", "Październik", "Listopad", "Grudzień"}),
        monthsInGerman({ "Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"});
    
    return nlohmann::json({
        {"pl", weekdaysInPolish[weekdayIndex] + ", " + std::to_string(dayOfMonthIndex) + " " + monthsInPolish[monthIndex]},
        {"en", weekdaysInEnglish[weekdayIndex] + ", " + std::to_string(dayOfMonthIndex) + " " + monthsInEnglish[monthIndex]}, 
        {"de", weekdaysInGerman[weekdayIndex] + ", " + std::to_string(dayOfMonthIndex) + " " + monthsInGerman[monthIndex]}, 
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
    
    std::string inEnglish = text, inPolish = "";
    
    if (text == "Clouds") {
        inPolish = "Zachmurzenie";
    } else if (text == "Rain") {
        inPolish = "Deszcz";
    } else if (text == "Snow") {
        inPolish = "Snieg";
    } else if (text == "Clear") {
        inPolish = "Bezchmurnie";
    } else if (text == "Drizzle") {
        inPolish = "Mzawka";
    } else if (text == "Thunderstorm") {
        inPolish = "Burza";
    } else if (text == "few clouds") {
        inPolish = "male\nzachmurzenie";
    } else if (text == "scattered clouds") {
        inPolish = "przejsciowe\nzachmurzenie";
    } else if (text == "broken clouds") {
        inPolish = "przebijace\nchmury";
    } else if (text == "clear sky") {
        inPolish = "bezchmurnie";
    } else if (text == "overcast clouds") {
        inPolish = "duze\nzachmurzenie";
    } else if (text == "light rain") {
        inPolish = "lekki\ndeszcz";
    } 
    
    std::replace(inEnglish.begin(), inEnglish.end(), ' ', '\n');
    return nlohmann::json({
        {"english", inEnglish},
        {"polish", inPolish}
    });
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