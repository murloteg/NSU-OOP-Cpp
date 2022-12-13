cmake_minimum_required(VERSION 3.23)
project(Sound_Processor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sound_Processor main.cpp)

find_package(Boost COMPONENTS program_options)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
include_directories(${BOOST_INCLUDE_LIBRARIES})

add_subdirectory(ParserWAV)
add_subdirectory(ConfigFile)
add_subdirectory(Converters)
add_subdirectory(SoundController)
add_subdirectory(Factory)
add_subdirectory(WAVFile)

target_include_directories(Sound_Processor PUBLIC ParserWAV ConfigFile SoundController Converters Factory WAVFile)
target_link_libraries(Sound_Processor PUBLIC Boost::program_options parser_wav_lib config_file_lib controller_lib converters_lib factory_lib wav_file_lib)
