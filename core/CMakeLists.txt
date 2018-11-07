cmake_minimum_required(VERSION 3.12)

project(EnvSel::Core LANGUAGES CXX)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_library(envselcore
        src/AbstractDomain.cpp
        src/Application.cpp
        src/ApplicationInstallation.cpp
        src/EnvSelLogging.cpp
        src/Environments.cpp
        src/IO.cpp
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
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
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
        cxx_std_11
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
        )

