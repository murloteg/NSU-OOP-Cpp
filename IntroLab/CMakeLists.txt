cmake_minimum_required(VERSION 3.23)
project(IntroLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(IntroLab main.cpp)

add_subdirectory(modules/module1)
add_subdirectory(modules/module2)
add_subdirectory(modules/module3)

target_include_directories(IntroLab PUBLIC modules/module1)
target_include_directories(IntroLab PUBLIC modules/module2)
target_include_directories(IntroLab PUBLIC modules/module3)

target_link_libraries(IntroLab PRIVATE module1_lib module2_lib module3_lib)
