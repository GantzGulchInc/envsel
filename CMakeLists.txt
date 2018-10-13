cmake_minimum_required (VERSION 2.6)

project (EnvironmentSelector)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

find_package(wxWidgets COMPONENTS core base REQUIRED)
# find_package(nlohmann_json 3.2.0 REQUIRED)

include( "${wxWidgets_USE_FILE}" )


file(GLOB SOURCES "src/*.cpp")

add_executable(EnvironmentSelector ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES} )


