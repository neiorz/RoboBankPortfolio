cmake_minimum_required(VERSION 3.10)
project(p4_Portfolio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers from this project and dependencies
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/p1_Calc/include
    ${CMAKE_SOURCE_DIR}/p2_Ledger/include
    ${CMAKE_SOURCE_DIR}/p3_Account/include
)

# Add the source files for the library
add_library(RoboBankPortfolio STATIC
    src/BaseAccount.cpp
    src/CheckingAccount.cpp
    src/SavingsAccount.cpp
    src/Portfolio.cpp
)

# Add the executable for testing
add_executable(RoboBankPortfolioDemo src/main.cpp)

# Link the executable to the library and its dependencies
target_link_libraries(RoboBankPortfolioDemo PRIVATE
    RoboBankPortfolio
    p1_Calc
    p2_Ledger
    p3_Account
)