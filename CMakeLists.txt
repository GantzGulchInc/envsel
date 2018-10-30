cmake_minimum_required(VERSION 3.12)

cmake_policy(VERSION 3.12)

project(EnvSel VERSION 1.0.1 LANGUAGES CXX)


#
# Build flags and configuration
#
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY  true)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# Third party libraries
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

#
# CLI11 Command line parser
#
add_subdirectory("ThirdParty/CLI11")

#
# Easy Logging++
#
add_definitions(-DELPP_THREAD_SAFE -DELPP_NO_DEFAULT_LOG_FILE)
set(build_static_lib ON)
add_subdirectory("ThirdParty/easyloggingpp" EXCLUDE_FROM_ALL)

#
# nlohman json
#
option(JSON_BuildTests "" OFF)
add_subdirectory("ThirdParty/json")

#
# wxWidgets
#
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

#
# googletest
#
add_subdirectory("ThirdParty/googletest")


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# EnvSel
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


enable_testing()

#
# EnvSel::Core
#
add_subdirectory("core")

#
# EnvSel::UI
#
add_subdirectory("ui")


#
# EnvSel::Test
#
add_subdirectory("test")

# add_test(NAME TestMain COMMAND TestMain)