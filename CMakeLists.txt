cmake_minimum_required(VERSION 3.14)
project(cpp_weather_app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++17-extensions")

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
        Frontend/Graphics/Inputs/Input.cpp
        Frontend/Graphics/Inputs/Input.h
        Frontend/Graphics/StaticText/StaticText.cpp
        Frontend/Graphics/StaticText/StaticText.h
        Frontend/Graphics/Font/CustomFont.cpp
        Frontend/Graphics/Font/CustomFont.h
        Frontend/Graphics/Image/Image.cpp
        Frontend/Graphics/Image/Image.h
        Frontend/Graphics/Containers/Div.cpp
        Frontend/Graphics/Containers/Div.h
        Frontend/Graphics/StaticText/CelsiusSign.cpp
        Frontend/Graphics/StaticText/CelsiusSign.h
        Frontend/Graphics/StaticText/CelsiusSign.cpp
        Frontend/Layout/Layout.cpp
        Frontend/Layout/Layout.h
        Backend/Helpers.cpp
        Backend/Helpers.h
)


add_executable(cpp_weather_app ${SOURCE_FILES})

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

find_package(CURL REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${SFML_INCLUDE_DIRS})

set(FONTS_DIR ${CMAKE_SOURCE_DIR}/Frontend/fonts)
file(COPY ${FONTS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(cpp_weather_app PRIVATE ${CMAKE_SOURCE_DIR}/Frontend/fonts)

configure_file(Frontend/Graphics/Images/background.jpg background.jpg COPYONLY)
configure_file(Frontend/Graphics/Images/WeatherIcons/sunset.png sunset.png COPYONLY)
configure_file(Frontend/Graphics/Images/WeatherIcons/sunrise.png sunrise.png COPYONLY)

file(GLOB IMAGE_FILES ${CMAKE_SOURCE_DIR}/Frontend/Graphics/Images/**/*.*)
file(COPY ${IMAGE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(cpp_weather_app PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


