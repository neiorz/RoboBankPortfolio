cmake_minimum_required(VERSION 3.10)
project(RoboBankCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(RoboBankCalc STATIC
    src/RoboBankCalc.cpp
    include/RoboBankCalc.hpp
)

add_library(RoboBankCalculator STATIC src/Calculator.cpp)
target_include_directories(RoboBankCalculator PUBLIC include)
