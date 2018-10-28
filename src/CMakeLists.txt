cmake_minimum_required(VERSION 3.12)

project(EnvSelLib)


add_library(${PROJECT_NAME} App.cpp SelectFrame.cpp ArgumentParser.cpp Domain.cpp IO.cpp NonCopyable.cpp SelectionTab.cpp Model.cpp ToString.cpp EditFrame.cpp EditApplicationPanel.cpp EnvSelLogging.cpp EnvSelLogging.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "../ThirdParty/easyloggingpp/src")

target_link_libraries(${PROJECT_NAME} easyloggingpp)
target_link_libraries(${PROJECT_NAME} CLI11::CLI11)
target_link_libraries(${PROJECT_NAME} nlohmann_json)
target_link_libraries(${PROJECT_NAME} LINK_INTERFACE_LIBRARIES ${wxWidgets_LIBRARIES})
