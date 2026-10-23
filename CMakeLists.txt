cmake_minimum_required(VERSION 3.14) # tells the computer not to try and build this project unless it has CMake version 3.14 or newer installed
project(poly_reg VERSION 1.0 LANGUAGES CXX) # sets project name to poly-reg, gives it a version 1.0 and specifies that it uses C++

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17) # ensures that compiler uses modern C++17 features. forces build to fail otherwise.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell C++ where public header files live
include_directories(include) # tells the compiler where the public header files (.hpp) live.

# Gather all .cpp source files from src/
file(GLOB SOURCES "src/*.cpp") # a wildcard search that looks inside src/ folder and gatherrs every .cpp file like matrix.cpp, preprocessing.cpp etc into a list named ${SOURCES}.

# Build the main reusable library
add_library(poly_reg_lib ${SOURCES}) #takes gathered .cpp implementation files from src/ and packages them into  a single reusable library bundle named poly_reg_lib.

# (Optional) Build tests if test files exist in tests/
file(GLOB TEST_SOURCES "tests/*.cpp") # finds every test file in tests/ folder, extracts the file name, turns each test file into a runnable program, links that test program with poly_reg_lib so that the tests can run with the Matrix and Preprocessing functions directly.
foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE poly_reg_lib)
endforeach()
