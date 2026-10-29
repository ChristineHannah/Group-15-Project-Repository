cmake_minimum_required(VERSION 3.14)
project(PolyRegLibrary VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17 standard compliance globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gather all core library implementation source files
set(POLYREG_SOURCES
    src/matrix.cpp
    src/csv_loader.cpp
    src/preprocessing.cpp
    src/feature_expansion.cpp
    src/polynomial_regression.cpp
)

# Build the main PolyReg static library target
add_library(poly_reg STATIC ${POLYREG_SOURCES})

# Attach public include directories directly to the library target
target_include_directories(poly_reg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Independent Test Executables
add_executable(test_matrix tests/test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE poly_reg)

add_executable(test_preprocessing tests/test_preprocessing.cpp)
target_link_libraries(test_preprocessing PRIVATE poly_reg)

add_executable(test_regression tests/test_regression.cpp)
target_link_libraries(test_regression PRIVATE poly_reg)

add_executable(test_gradient_descent tests/test_gradient_descent.cpp)
target_link_libraries(test_gradient_descent PRIVATE poly_reg)

# Demonstration Executable Targets (4 Demos)
add_executable(run_demo examples/polynomial_regression_demo.cpp)
target_link_libraries(run_demo PRIVATE poly_reg)

add_executable(run_gd_demo examples/gradient_descent_demo.cpp)
target_link_libraries(run_gd_demo PRIVATE poly_reg)

add_executable(run_export_demo examples/preprocessing_export_demo.cpp)
target_link_libraries(run_export_demo PRIVATE poly_reg)

add_executable(run_graph_demo examples/ascii_graph_demo.cpp)
target_link_libraries(run_graph_demo PRIVATE poly_reg)

# Enable testing framework integration
enable_testing()
add_test(NAME MatrixTest COMMAND test_matrix)
add_test(NAME PreprocessingTest COMMAND test_preprocessing)
add_test(NAME RegressionTest COMMAND test_regression)
add_test(NAME GradientDescentTest COMMAND test_gradient_descent)