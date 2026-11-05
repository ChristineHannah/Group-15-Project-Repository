cmake_minimum_required(VERSION 3.14) #Ensuring cmake version is at least version 3.14 for compatibility with modern CMake features
project(PolyRegLibrary VERSION 1.0.0 LANGUAGES CXX) #The version of the project is set to 1.0.0 and the language is specified as C++

# This enforces the C++17 standard compliance globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) #Tells the compiler to disable compiler specific extensions and adhere to standard ISO (defines syntax, standard library behaviour, etc) C++

# This tells the compiler how to gather all core library implementation source files setting them as POLYREG_SOURCES variable for later use in the add_library command. This makes the add_library command cleaner and easier to read.
set(POLYREG_SOURCES
    src/matrix.cpp
    src/csv_loader.cpp
    src/preprocessing.cpp
    src/feature_expansion.cpp
    src/polynomial_regression.cpp
)

# Tells the compiler how to build the main PolyReg static library target
add_library(poly_reg STATIC ${POLYREG_SOURCES})
#A static library is a collection of object files that are linked into the program during the linking phase of compilation, and they become part of the executable.

# Attach public include directories directly to the library target
target_include_directories(poly_reg PUBLIC #Tells the compiler where to look for header files during the compliation stage of compiling the library. PUBLIC means the include directory is required when building the library and is also passed along to anything that links to that library such as tests and demo executable - it ensures that any file can easily write #include "poly_reg/matrix.hpp".
    ${CMAKE_CURRENT_SOURCE_DIR}/include #built in CMake varaible. It guarantees a path to the headers regardless of where the build command is run from.
)

# Independent Test Executables
add_executable(test_matrix tests/test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE poly_reg) #It tells CMake that : when you complie test_matrix, grab all the compiled machine code from poly_reg and weld them together such that the executable has all it needs to run. PRIVATE means that the library is only used for this target.

add_executable(test_preprocessing tests/test_preprocessing.cpp)
target_link_libraries(test_preprocessing PRIVATE poly_reg)

add_executable(test_regression tests/test_regression.cpp)
target_link_libraries(test_regression PRIVATE poly_reg)

add_executable(test_gradient_descent tests/test_gradient_descent.cpp)
target_link_libraries(test_gradient_descent PRIVATE poly_reg)

# Demonstration Executable Targets (4 Demos)
add_executable(run_demo examples/polynomial_regression_demo.cpp)
target_link_libraries(run_demo PRIVATE poly_reg)


add_executable(run_graph_demo examples/ascii_graph_demo.cpp)
target_link_libraries(run_graph_demo PRIVATE poly_reg)

# Enable testing framework integration
enable_testing() #Activates CMake's built - in testing framework. Tells it that the project contaiins automated tests.
add_test(NAME MatrixTest COMMAND test_matrix)
add_test(NAME PreprocessingTest COMMAND test_preprocessing)
add_test(NAME RegressionTest COMMAND test_regression)
