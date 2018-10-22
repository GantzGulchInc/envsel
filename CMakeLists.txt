cmake_minimum_required(VERSION 3.12)

project(EnvSel)

set(EnvSel_VERSION_MAJOR 1)
set(EnvSel_VERSION_MINOR 0)
set(EnvSel_VERSION_BUGFIX 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -std=c++17")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY  true)
set(PROJECT_SOURCE_DIR "src")

configure_file(
        "${PROJECT_SOURCE_DIR}/EnvSelConfig.h.in"
        "${PROJECT_BINARY_DIR}/EnvSelConfig.h"
)

#
# Easy Logging++
#
add_definitions(-DELPP_THREAD_SAFE -DELPP_NO_DEFAULT_LOG_FILE)
set(build_static_lib ON)
add_subdirectory("ThirdParty/easyloggingpp" EXCLUDE_FROM_ALL)

#
# wxWidgets
#
find_package(wxWidgets COMPONENTS core base REQUIRED)

include("${wxWidgets_USE_FILE}")

add_executable(${PROJECT_NAME} src/App.cpp src/SelectFrame.cpp src/ArgumentParser.cpp src/Domain.cpp src/Main.cpp src/IO.cpp src/NonCopyable.cpp src/SelectionTab.cpp src/Model.cpp src/ToString.cpp)

target_link_libraries(${PROJECT_NAME} easyloggingpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${PROJECT_BINARY_DIR}")

#
# Third party libraries
#
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/CLI11/include")
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/json/single_include")
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "ThirdParty/easyloggingpp/src")


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION $ENV{HOME}/bin )

