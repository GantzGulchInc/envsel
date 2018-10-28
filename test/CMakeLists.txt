cmake_minimum_required(VERSION 3.12)

project(EnvSelTest)

set(TestMain "TestMain")

enable_testing()

#
# TEXT EXECUTABLE
#
add_executable(${TestMain} Test.cpp ScriptVariableTest.cpp)
target_link_libraries(${TestMain} EnvSelLib)
target_link_libraries(${TestMain} gtest)

# add_test(NAME TestMain COMMAND TestMain)