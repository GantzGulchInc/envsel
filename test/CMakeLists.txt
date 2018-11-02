cmake_minimum_required(VERSION 3.12)

project(EnvSel::Test)


#
# TEXT EXECUTABLE
#
add_executable(envseltest
        src/Test.cpp
        src/EnvSelTest.cpp
        src/DomainTest.cpp
        )

target_include_directories(envseltest
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        src
        )

target_include_directories(envseltest
        SYSTEM PUBLIC
        "${Easyloggingpp_SOURCE_DIR}/src"
        )


target_compile_features(envseltest
        PUBLIC
        cxx_std_17
        )

target_compile_options(envseltest
        PRIVATE
        -pedantic -Wall -Wextra
        )

target_link_libraries(envseltest
        PUBLIC
        EnvSel::Core
        gtest
        easyloggingpp
        CLI11::CLI11
        nlohmann_json
        ${wxWidgets_LIBRARIES}
        )

add_test(NAME TestMain COMMAND envseltest)