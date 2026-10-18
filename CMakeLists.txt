cmake_minimum_required(VERSION 3.14)
project(PolyRegLibrary VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 standard globally across all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define include directory paths so headers are globally accessible via "poly_reg/..."
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Gather all core source files contributed by team members
set(POLYREG_SOURCES
    src/matrix.cpp
    src/csv_loader.cpp
    src/preprocessing.cpp
    src/feature_expansion.cpp
)

# Build the main PolyReg object-oriented library target
add_library(poly_reg STATIC ${POLYREG_SOURCES})

# Build the test suites (integrating Joseph's unit tests)
add_executable(run_tests 
    tests/test_matrix.cpp
    tests/test_preprocessing.cpp
)

# Link the test suite executable with the core library target
target_link_libraries(run_tests PRIVATE poly_reg)

# Optional: Enable testing framework integration
enable_testing()
add_test(NAME MatrixAndPreprocessingTests COMMAND run_tests)