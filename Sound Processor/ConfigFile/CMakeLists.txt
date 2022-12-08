add_library(config_file_lib STATIC ConfigFile.cpp ConfigFile.h)

target_include_directories(config_file_lib PUBLIC ../Converters)
target_link_libraries(config_file_lib PUBLIC converters_lib)