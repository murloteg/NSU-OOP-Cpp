cmake_minimum_required(VERSION 3.23)
project(intro_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(intro_lab main.cpp)

add_subdirectory(modules/module1)
add_subdirectory(modules/module2)
add_subdirectory(modules/module3)

target_include_directories(intro_lab PUBLIC modules/module1)
target_include_directories(intro_lab PUBLIC modules/module2)
target_include_directories(intro_lab PUBLIC modules/module3)

target_link_libraries(intro_lab PRIVATE module1_lib module2_lib module3_lib)
