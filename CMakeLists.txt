cmake_minimum_required(VERSION 3.10)
project(RoboBank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all subprojects
add_subdirectory(p1_Calc)
add_subdirectory(p2_Ledger)
add_subdirectory(p3_Account)
add_subdirectory(p4_Portfolio)
