cmake_minimum_required(VERSION 3.23)
project(Sound_Processor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sound_Processor main.cpp)

add_subdirectory(CommandLineParser)
add_subdirectory(ParserWAVHeader)
add_subdirectory(ConfigFileParser)
add_subdirectory(Converters)
add_subdirectory(SoundController)
add_subdirectory(Factory)
add_subdirectory(Description)

target_include_directories(Sound_Processor PUBLIC CommandLineParser ParserWAVHeader ConfigFileParser SoundController Converters Factory Description)
target_link_libraries(Sound_Processor PUBLIC command_line_parser
                                            parser_wav_lib
                                            parser_config_file_lib
                                            controller_lib
                                            converters_lib
                                            factory_lib
                                            description_lib)
