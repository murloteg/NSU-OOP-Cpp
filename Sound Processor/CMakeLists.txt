cmake_minimum_required(VERSION 3.23)
project(Sound_Processor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sound_Processor main.cpp)

find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
include_directories(${BOOST_INCLUDE_LIBRARIES})

add_subdirectory(ParserWAV)
target_include_directories(Sound_Processor PUBLIC ParserWAV)
target_link_libraries(Sound_Processor PUBLIC ${Boost_LIBRARIES} parser_wav_lib)
