cmake_minimum_required(VERSION 3.23)
project(Dilemma)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)

#add_executable(Dilemma main.cpp) # standard application
add_executable(Dilemma Tests/my_tests.cpp) # my_tests
include_directories(${BOOST_INCLUDE_LIBRARIES})
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(Strategies)
add_subdirectory(Factory)
add_subdirectory(GameController)
add_subdirectory(Modes)
add_subdirectory(Tests)
target_include_directories(Dilemma PUBLIC Strategies Factory GameController Modes Tests)
target_link_libraries(Dilemma PUBLIC Boost::program_options strategies_lib factory_lib game_controller_lib modes_lib gtest_main tests_lib)
