cmake_minimum_required(VERSION 3.16)
project(LogAnalyser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#---include directories---
include_directories(include)

#---Library---
add_library(log_analyser_lib
	src/LogAnalyser.cpp
	src/TextLogParser.cpp
	src/JsonLogParser.cpp
)

#---Main Executable--- 
add_executable(log_analyser 
	src/main.cpp
)

target_link_libraries(log_analyser
	log_analyser_lib
)

#---Google Test---
enable_testing()

find_package(GTest REQUIRED)

#---Test Executable---
add_executable(runTests
	tests/test_log_analyser.cpp
)

target_link_libraries(runTests
	log_analyser_lib
	GTest::GTest
	GTest::Main
)

#---Register Test---
add_test(NAME logTests COMMAND runTests)
