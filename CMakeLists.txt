cmake_minimum_required(VERSION 3.16)
project(LogAnalyser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)


#main app
add_executable(log_analyser 
	src/main.cpp
	src/LogAnalyser.cpp
)

#testing
enable_testing()

find_package(GTest REQUIRED)

add_executable(runTests
	tests/test_log_analyser.cpp
	src/LogAnalyser.cpp
)

target_include_directories(log_analyser PRIVATE include)
target_include_directories(runTests PRIVATE include)

target_link_libraries(runTests GTest::GTest GTest::Main pthread)

add_test(NAME logTests COMMAND runTests)
