cmake_minimum_required(VERSION 3.12)

project(EnvSel::Core LANGUAGES CXX)


add_library(envselcore
        src/Application.cpp
        src/ApplicationInstallation.cpp
        src/EnvSelLogging.cpp
        src/Environments.cpp
        src/IO.cpp
        src/NonCopyable.cpp
        src/Project.cpp
        src/ProjectApp.cpp
        src/Script.cpp
        src/ScriptCommand.cpp
        src/ScriptVariable.cpp
        src/ToString.cpp
        )

add_library(EnvSel::Core ALIAS envselcore)

target_include_directories(envselcore
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src
        )

target_include_directories(envselcore
        SYSTEM PUBLIC
        "${Easyloggingpp_SOURCE_DIR}/src"
        )


target_compile_features(envselcore
        PUBLIC
        cxx_std_17
        )

target_compile_options(envselcore
        PRIVATE
        -pedantic -Wall -Wextra
        )

target_link_libraries(envselcore
        PUBLIC
        easyloggingpp
        CLI11::CLI11
        nlohmann_json
        ${wxWidgets_LIBRARIES}
        )


# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#    message(STATUS "MLG Variable: ${_variableName}=${${_variableName}}")
# endforeach()

