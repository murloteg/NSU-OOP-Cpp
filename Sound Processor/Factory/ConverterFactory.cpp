#include "ConverterFactory.h"

std::shared_ptr<Converter> ConverterFactory::createConverter(std::string nameOfConverter, unsigned int bufferSize,
                                             unsigned int firstParameter, unsigned int secondParameter)
{
    auto converterName = converters.find(nameOfConverter);
    switch (converterName->second)
    {
        case MUTE:
        {
            return std::shared_ptr<Converter>(new Mute(bufferSize, firstParameter, secondParameter));
        }

        case MIX:
        {
            return std::shared_ptr<Converter>(new Mix(bufferSize, firstParameter, secondParameter));
        }

        case RANDOMIZER:
        {
            return std::shared_ptr<Converter>(new Randomizer(bufferSize, firstParameter, secondParameter));
        }

        case SLOW:
        {
            return std::shared_ptr<Converter>(new Slow(bufferSize, firstParameter, secondParameter));
        }

        default:
        {
            return nullptr;
        }
    }
}
