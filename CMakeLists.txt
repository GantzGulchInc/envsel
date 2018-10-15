cmake_minimum_required (VERSION 3.12)

project (EnvironmentSelector)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++17)

#
# wxWidgets
#
find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

#
# Third party libraries
#
include_directories( "ThirdParty/CLI11/include" )
include_directories( "ThirdParty/json/single_include" )

#
# Sources
#
file(GLOB SOURCES "src/*.cpp")
set( E_SOURCES ${SOURCES} )


add_executable(EnvironmentSelector ${E_SOURCES} )

target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES} )


