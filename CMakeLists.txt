# Root CMakeLists.txt (Christine's Final Week 4 Build Script)
cmake_minimum_required(VERSION 3.14)
project(PolyRegLibrary VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(POLYREG_SOURCES
    src/matrix.cpp
    src/csv_loader.cpp
    src/preprocessing.cpp
    src/feature_expansion.cpp
    src/polynomial_regression.cpp
)

add_library(poly_reg STATIC ${POLYREG_SOURCES})

target_include_directories(poly_reg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Test Executable Target (Joseph's Unit Tests)
add_executable(run_tests
    tests/test_matrix.cpp
    tests/test_preprocessing.cpp
    tests/test_regression.cpp
    tests/test_gradient_descent.cpp
)
target_link_libraries(run_tests PRIVATE poly_reg)

# Demonstration Executable Target (Allan's Demo)
add_executable(run_demo
    examples/polynomial_regression_demo.cpp
)
target_link_libraries(run_demo PRIVATE poly_reg)

enable_testing()
add_test(NAME FinalProjectTests COMMAND run_tests)