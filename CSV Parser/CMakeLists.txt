cmake_minimum_required(VERSION 3.23)
project(CSV_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(CSV_Parser main.cpp)


add_subdirectory(Tuple)
add_subdirectory(CSVParser)

target_include_directories(CSV_Parser PUBLIC Tuple)
target_include_directories(CSV_Parser PUBLIC CSVParser)
target_link_libraries(CSV_Parser PUBLIC tuple_lib csv_parser_lib)
