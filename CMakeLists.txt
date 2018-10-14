cmake_minimum_required (VERSION 2.6)

project (EnvironmentSelector)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)


find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

include_directories( "ThirdParty/CLI11/include" )


file(GLOB SOURCES "src/*.cpp")

set( E_SOURCES ${SOURCES} )

add_executable(EnvironmentSelector ${E_SOURCES} )

target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES} )


