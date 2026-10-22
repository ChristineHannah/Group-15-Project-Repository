cmake_minimum_required(VERSION 3.14)
project(PolyRegLibrary VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17 standard compliance globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gather all core library implementation source files (Weeks 1 through 3)
set(POLYREG_SOURCES
    src/matrix.cpp
    src/csv_loader.cpp
    src/preprocessing.cpp
    src/feature_expansion.cpp
    src/polynomial_regression.cpp
)

# Build the main PolyReg static library target
add_library(poly_reg STATIC ${POLYREG_SOURCES})

# Attach public include directories directly to the library target using modern CMake standards
target_include_directories(poly_reg PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Build Executable 1: Unit Test Suite Target (Joseph)
add_executable(run_tests
    tests/test_matrix.cpp
    tests/test_preprocessing.cpp
    tests/test_regression.cpp
)
target_link_libraries(run_tests PRIVATE poly_reg)

# Build Executable 2: End-to-End Demonstration Target (Allan)
add_executable(run_demo
    examples/polynomial_regression_demo.cpp
)
target_link_libraries(run_demo PRIVATE poly_reg)

# Enable testing framework integration
enable_testing()
add_test(NAME IntegrationTests COMMAND run_tests)