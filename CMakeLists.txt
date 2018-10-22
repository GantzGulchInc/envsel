cmake_minimum_required (VERSION 3.12)

project (EnvSel)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

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
include_directories( "ThirdParty/easyloggingpp/src" )

#
# Sources
#
# file(GLOB SOURCES "src/*.cpp")
set( L_SOURCES ThirdParty/easyloggingpp/src/easylogging++.cc)

set( E_SOURCES src/App.cpp src/SelectFrame.cpp src/ArgumentParser.cpp src/Domain.cpp src/Main.cpp src/IO.cpp src/NonCopyable.cpp src/NonCopyable.h src/SelectionTab.cpp src/SelectionTab.h src/Model.cpp src/Model.h src/ToString.cpp src/ToString.h)


add_executable(EnvSel ${E_SOURCES} ${L_SOURCES})

target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES} )


