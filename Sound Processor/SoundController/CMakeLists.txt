add_library(controller_lib STATIC SoundController.cpp SoundController.h)
target_include_directories(controller_lib PUBLIC ../ParserWAVHeader ../ConfigFileParser ../Converters ../Factory)
target_link_libraries(controller_lib PUBLIC parser_wav_lib parser_config_file_lib converters_lib factory_lib)
