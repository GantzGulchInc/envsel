cmake_minimum_required(VERSION 3.12)

project(EnvSel::UI LANGUAGES CXX)

configure_file(
        "${PROJECT_SOURCE_DIR}/src/EnvSelConfig.h.in"
        "${PROJECT_BINARY_DIR}/include/EnvSelConfig.h"
)

add_executable(envsel
        src/App.cpp
        src/Arguments.cpp
        src/ArgumentParser.cpp
        src/EditApplicationPanel.cpp
        src/EditFrame.cpp
        src/Main.cpp
        src/Model.cpp
        src/SelectFrame.cpp
        src/SelectionTab.cpp
        )

target_include_directories(envsel
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src
        "${PROJECT_BINARY_DIR}"
        )

target_include_directories(envsel
        SYSTEM PUBLIC
        "${Easyloggingpp_SOURCE_DIR}/src"
        )


target_compile_features(envsel
        PUBLIC
        cxx_std_11
        )

target_compile_options(envsel
        PRIVATE
        -pedantic -Wall -Wextra
        )

target_link_libraries(envsel
        PUBLIC
        EnvSel::Core
        CLI11::CLI11
        ${wxWidgets_LIBRARIES}
        )

install(TARGETS envsel DESTINATION bin)
install(PROGRAMS EnvSel DESTINATION bin)


# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#    message(STATUS "MLG Variable: ${_variableName}=${${_variableName}}")
# endforeach()

