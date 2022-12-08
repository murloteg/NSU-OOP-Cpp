add_library(csv_parser_lib STATIC CSVParser.cpp CSVParser.h)

target_include_directories(csv_parser_lib PUBLIC ../Tuple)
target_link_libraries(csv_parser_lib PUBLIC tuple_lib)
