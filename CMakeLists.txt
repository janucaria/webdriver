cmake_minimum_required(VERSION 3.23)

project(webdriver LANGUAGES CXX)

include(CTest)

find_package(fmt REQUIRED)
find_package(httplib REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(sources)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

