//
// Created by Kamil Krawczyk on 29/04/2024.
//

#include "Helpers.h"

std::string Helpers::replaceAll(std::string str, const std::string from, const std::string to) {
    if (from.empty())
        return str;

    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return str;
}

int Helpers::toCelsius(const double kelvins, int digits) {
    if (digits == 0)
        return 0;
    return round((kelvins - 273.15));
}

std::string Helpers::convertToClockFormat(time_t unix) {
    struct tm * timeinfo;
    timeinfo = localtime(&unix);
    char buffer[6];
    strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

    return buffer;
}

std::string Helpers::getWeekday(const std::string date) {
    std::tm timeInfo = {};
    std::istringstream ss(date);
    ss >> std::get_time(&timeInfo, "%Y-%m-%d");

    if (ss.fail()) {
        // Parsing failed
        return "Invalid Date";
    }

    std::time_t time = std::mktime(&timeInfo);
    if (time == -1) {
        // Conversion failed
        return "Invalid Date";
    }

    const std::vector<std::string> weekdays({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"});

    return weekdays.at(timeInfo.tm_wday);
}
