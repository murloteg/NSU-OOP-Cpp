add_library(config_file_lib STATIC ConfigFile.cpp ConfigFile.h)
target_include_directories(config_file_lib PUBLIC ../Converters ../ConverterFactory)
target_link_libraries(config_file_lib PUBLIC converters_lib factory_lib)