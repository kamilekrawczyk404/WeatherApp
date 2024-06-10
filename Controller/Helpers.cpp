//
// Created by Kamil Krawczyk on 29/04/2024.
//

#include "Helpers.h"

int Helpers::toCelsius(const double kelvins, int digits) {
    if (digits == 0)
        return 0;
    return round((kelvins - 273.15));
}

// format is like "HH:MM"
// H - hours
// M - minutes
std::string Helpers::convertToClockFormat(time_t unix, int shift,  int currentGMTOffset) {
    unix -= currentGMTOffset;
    unix += shift;
    
    struct tm * timeinfo;
    timeinfo = localtime(&unix);
    char buffer[6];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

    return buffer;
}

// returns full date based on a unix time
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

std::string Helpers::urlEncode(const std::string &value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        // keep alphanumeric and other accepted characters intact
        if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else if (c == ' ') {
            // encode space as %20
            escaped << "%20";
        } else {
            // any other characters are percent-encoded
            escaped << '%' << std::setw(2) << std::uppercase << int(static_cast<unsigned char>(c));
        }
    }

    return escaped.str();
}
