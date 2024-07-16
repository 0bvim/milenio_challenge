cmake_minimum_required(VERSION 3.10)
project(MilenioChallenge)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source directory
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add the executable
add_executable(CsvHandler
    src/main.cpp
    src/libcsv.cpp
    src/utils.cpp
)

# Enable testing
enable_testing()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create a test executable
add_executable(runTests
    tests/main.cpp
    tests/tests.cpp
    src/libcsv.cpp
    src/utils.cpp
)

# Link GoogleTest to the test executable
target_link_libraries(runTests gtest gtest_main)

# Add test
add_test(NAME runTests COMMAND runTests)
