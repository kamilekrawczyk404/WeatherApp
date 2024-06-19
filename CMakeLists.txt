cmake_minimum_required(VERSION 3.14)
project(cpp_weather_app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++17-extensions")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(IMAGE_DIR "${CMAKE_SOURCE_DIR}/public/images")
set(FONTS_DIR "${CMAKE_SOURCE_DIR}/public/fonts")

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/**/*.cpp" "${SOURCE_DIR}/**/*.h")
file(COPY ${FONTS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${IMAGE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${FONTS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(cpp_weather_app main.cpp ${SOURCES})

include_directories(${SOURCE_DIR} ${IMAGE_DIR} ${FONTS_DIR})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "./cmake-build-debug")


#add_custom_target(copy_images ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${IMAGE_DIR} ${CMAKE_BINARY_DIR}/images
#)
#
#add_dependencies(cpp_weather_app copy_images)
#add_definitions(-DIMAGE_PATH="${CMAKE_BINARY_DIR}/images")

target_link_libraries(cpp_weather_app PRIVATE nlohmann_json::nlohmann_json ${CURL_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
