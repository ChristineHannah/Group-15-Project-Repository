cmake_minimum_required(VERSION 3.14)
project(poly_reg VERSION 1.0 LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell C++ where public header files live
include_directories(include)

# Gather all .cpp source files from src/
file(GLOB SOURCES "src/*.cpp")

# Build the main reusable library
add_library(poly_reg_lib ${SOURCES})

# (Optional) Build tests if test files exist in tests/
file(GLOB TEST_SOURCES "tests/*.cpp")
foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE poly_reg_lib)
endforeach()
