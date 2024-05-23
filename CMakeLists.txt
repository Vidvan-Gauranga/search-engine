cmake_minimum_required (VERSION 3.5)

project ("search_engine" VERSION 1.0)

set (CMAKE_CXX_STANDART 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (MY_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_subdirectory (nlohmann_json)
add_subdirectory (src)
add_subdirectory (tests)


