cmake_minimum_required(VERSION 3.14)
project(cpp_weather_app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++17-extensions")

set(SOURCE_FILES main.cpp
        Controller/Weather.cpp
        Controller/Weather.h
        Controller/Location.cpp
        Controller/Location.h
        Controller/FetchAPI.cpp
        Controller/FetchAPI.h
        Controller/KEYS.cpp
        Controller/KEYS.h
        View/Graphics/Inputs/Input.cpp
        View/Graphics/Inputs/Input.h
        View/Graphics/StaticText/StaticText.cpp
        View/Graphics/StaticText/StaticText.h
        View/Graphics/Font/CustomFont.cpp
        View/Graphics/Font/CustomFont.h
        View/Graphics/Image/Image.cpp
        View/Graphics/Image/Image.h
        View/Graphics/Containers/Div.cpp
        View/Graphics/Containers/Div.h
        View/Graphics/StaticText/CelsiusSign.cpp
        View/Graphics/StaticText/CelsiusSign.h
        View/Graphics/StaticText/CelsiusSign.cpp
        View/Layout/Layout.cpp
        View/Layout/Layout.h
        Controller/Helpers.cpp
        Controller/Helpers.h
        Controller/LocationImage.cpp
        Controller/LocationImage.h
        View/Graphics/Checkbox/Checkbox.cpp
        View/Graphics/Checkbox/Checkbox.h
        View/Graphics/Containers/Circle.cpp
        View/Graphics/Containers/Circle.h
        View/Layout/Chart.cpp
        View/Layout/Chart.h
        Controller/TranslationAPI.cpp
        Controller/TranslationAPI.h
)

add_executable(cpp_weather_app ${SOURCE_FILES})

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(FONTS_DIR ${CMAKE_SOURCE_DIR}/View/fonts)
file(COPY ${FONTS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(cpp_weather_app PRIVATE ${CMAKE_SOURCE_DIR}/View/fonts)

configure_file(View/Graphics/Images/background.jpg background.jpg COPYONLY)
configure_file(View/Graphics/Images/Components/checked.png checked.png COPYONLY)
configure_file(View/Graphics/Images/Components/unchecked.png unchecked.png COPYONLY)
configure_file(View/Graphics/Images/CountriesFlags/pl.png pl.png COPYONLY)
configure_file(View/Graphics/Images/CountriesFlags/de.png ge.png COPYONLY)
configure_file(View/Graphics/Images/CountriesFlags/en.png gb.png COPYONLY)

file(GLOB IMAGE_FILES ${CMAKE_SOURCE_DIR}/Frontend/Graphics/Images/**/*.*)
file(COPY ${IMAGE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(cpp_weather_app PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


