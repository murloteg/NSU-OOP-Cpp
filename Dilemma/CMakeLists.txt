cmake_minimum_required(VERSION 3.23)
project(Dilemma)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)

add_executable(Dilemma main.cpp)
include_directories(${BOOST_INCLUDE_LIBRARIES})

add_subdirectory(Strategies)
add_subdirectory(Factory)
add_subdirectory(GameController)
add_subdirectory(Modes)
target_include_directories(Dilemma PUBLIC Strategies Factory GameController Modes)
target_link_libraries(Dilemma PUBLIC Boost::program_options strategies_lib factory_lib game_controller_lib modes_lib)
