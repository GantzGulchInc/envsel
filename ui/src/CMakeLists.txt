cmake_minimum_required(VERSION 3.12)

project(EnvSelLib LANGUAGES CXX)


add_library(${PROJECT_NAME} App.cpp SelectFrame.cpp ArgumentParser.cpp Domain.cpp IO.cpp NonCopyable.cpp SelectionTab.cpp Model.cpp ToString.cpp EditFrame.cpp EditApplicationPanel.cpp EnvSelLogging.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -pedantic -Wall -Wextra)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)


# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#    message(STATUS "MLG Variable: ${_variableName}=${${_variableName}}")
# endforeach()

target_include_directories(${PROJECT_NAME}
    SYSTEM PUBLIC
        "${Easyloggingpp_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        easyloggingpp CLI11::CLI11 nlohmann_json ${wxWidgets_LIBRARIES}
)
