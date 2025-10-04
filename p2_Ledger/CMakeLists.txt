# CMake for RoboBank Ledger
add_library(RoboBankLedger STATIC
    src/Ledger.cpp
)

target_include_directories(RoboBankLedger PUBLIC include)
