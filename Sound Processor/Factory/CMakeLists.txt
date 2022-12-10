add_library(factory_lib STATIC ConverterFactory.cpp ConverterFactory.h)
target_include_directories(factory_lib PUBLIC ../Converters ../SoundController)
target_link_libraries(factory_lib PUBLIC converters_lib controller_lib)