cmake_minimum_required(VERSION 3.12)

project(EnvSel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -std=c++17")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

#
# Easy Logging++
#
add_definitions(-DELPP_THREAD_SAFE -DELPP_NO_DEFAULT_LOG_FILE)
set(build_static_lib ON)
add_subdirectory("ThirdParty/easyloggingpp")

#
# wxWidgets
#
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

#
# Third party libraries
#
include_directories(SYSTEM "ThirdParty/CLI11/include")
include_directories(SYSTEM "ThirdParty/json/single_include")
include_directories(SYSTEM "ThirdParty/easyloggingpp/src")

set(E_SOURCES src/App.cpp src/SelectFrame.cpp src/ArgumentParser.cpp src/Domain.cpp src/Main.cpp src/IO.cpp src/NonCopyable.cpp src/NonCopyable.h src/SelectionTab.cpp src/SelectionTab.h src/Model.cpp src/Model.h src/ToString.cpp src/ToString.h)


add_executable(EnvSel ${E_SOURCES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} easyloggingpp)


