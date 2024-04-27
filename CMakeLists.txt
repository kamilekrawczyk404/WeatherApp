cmake_minimum_required(VERSION 3.14)
project(cpp_weather_app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Weather.cpp
        Weather.h
        Location.cpp
        Location.h
        HandleJson.cpp
        HandleJson.h
        FetchAPI.cpp
        FetchAPI.h)
add_executable(cpp_weather_app ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

find_package(CURL REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${SFML_INCLUDE_DIRS})
target_link_libraries(cpp_weather_app PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


