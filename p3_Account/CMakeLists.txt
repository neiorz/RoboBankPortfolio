cmake_minimum_required(VERSION 3.10)
project(RoboBankAccount)

set(CMAKE_CXX_STANDARD 11)

# include headers 
include_directories(include)

# RoboBankAccount
add_executable(RoboBankAccount
    src/Account.cpp
    src/main.cpp
)

# ---------------------------
#connet with RoboBankLedger
# ------------------------------
add_library(RoboBankLedger STATIC
    ../RoboBankLedger/src/RoboBankLedger.cpp
)

target_include_directories(RoboBankLedger PUBLIC
    ../RoboBankLedger/include
)

# RoboBankAccount with RoboBankLedger
target_link_libraries(RoboBankAccount RoboBankLedger)
