cmake_minimum_required(VERSION 3.5)

project(qserialtest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 CONFIG REQUIRED Core SerialPort)

add_executable(qserialtest main.cpp)
target_link_libraries(qserialtest Qt5::Core Qt5::SerialPort)
