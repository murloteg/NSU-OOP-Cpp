cmake_minimum_required(VERSION 3.23)
project(homework_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework_cpp main.cpp)

add_subdirectory(TestClass)

target_include_directories(homework_cpp PUBLIC TestClass)
target_link_libraries(homework_cpp PRIVATE my_class_lib)
