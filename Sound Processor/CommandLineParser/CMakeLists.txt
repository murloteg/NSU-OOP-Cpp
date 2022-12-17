add_library(command_line_parser STATIC CommandLineParser.cpp CommandLineParser.h)

find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
include_directories(${BOOST_INCLUDE_LIBRARIES})

target_include_directories(command_line_parser PUBLIC ../Description)
target_link_libraries(command_line_parser PUBLIC Boost::program_options description_lib)
