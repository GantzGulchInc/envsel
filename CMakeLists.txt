cmake_minimum_required(VERSION 3.12)

project(EnvSel)

#
# Project Version
#
set(EnvSel_VERSION_MAJOR 1)
set(EnvSel_VERSION_MINOR 0)
set(EnvSel_VERSION_BUGFIX 0)

configure_file(
        "${PROJECT_SOURCE_DIR}/src/EnvSelConfig.h.in"
        "${PROJECT_BINARY_DIR}/EnvSelConfig.h"
)

#
# Build flags and configuration
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -std=c++17")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY  true)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Third party libraries
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#
# CLI11 Command line parser
#
add_subdirectory("ThirdParty/CLI11")

#
# Easy Logging++
#
add_definitions(-DELPP_THREAD_SAFE -DELPP_NO_DEFAULT_LOG_FILE)
set(build_static_lib ON)
add_subdirectory("ThirdParty/easyloggingpp" EXCLUDE_FROM_ALL)

#
# nlohman json
#
add_subdirectory("ThirdParty/json")

#
# wxWidgets
#
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

#
# googletest
#
add_subdirectory("ThirdParty/googletest")


#
# EnvSelLib
#
add_subdirectory("src")


#
# MAIN EXECUTABLE
#
add_executable(${PROJECT_NAME} Main.cpp )

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} EnvSelLib)



add_subdirectory("test")

#
# Third party libraries
#
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/CLI11/include")
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/json/single_include")
# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/easyloggingpp/src")

add_test(NAME TestMain COMMAND TestMain)