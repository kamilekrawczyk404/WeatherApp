cmake_minimum_required(VERSION 3.14)
project(cpp_weather_app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Backend/Weather.cpp
        Backend/Weather.h
        Backend/Location.cpp
        Backend/Location.h
        Backend/HandleJson.cpp
        Backend/HandleJson.h
        Backend/FetchAPI.cpp
        Backend/FetchAPI.h
        Backend/KEYS.cpp
        Backend/KEYS.h
        Graphics/Inputs/Input.cpp
        Graphics/Inputs/Input.h
        Graphics/StaticText/StaticText.cpp
        Graphics/StaticText/StaticText.h
        Graphics/Font/CustomFont.cpp
        Graphics/Font/CustomFont.h
)


add_executable(cpp_weather_app ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

find_package(CURL REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${SFML_INCLUDE_DIRS})

set(FONTS_DIR ${CMAKE_SOURCE_DIR}/fonts)
file(COPY ${FONTS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(cpp_weather_app PRIVATE ${CMAKE_SOURCE_DIR}/fonts)

target_link_libraries(cpp_weather_app PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


