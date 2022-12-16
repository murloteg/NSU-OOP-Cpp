#include "ConverterFactory.h"

std::shared_ptr<Converter> ConverterFactory::createConverter(std::string nameOfConverter, int bufferSize,
                                             unsigned int firstParameter, unsigned int secondParameter)
{
    auto converterName = converters.find(nameOfConverter);
    switch (converterName->second)
    {
        // TODO: finish this block.
        case MUTE:
        {

            return std::shared_ptr<Converter>(new Mute(bufferSize, firstParameter, secondParameter));
        }

        case MIX:
        {
            return std::shared_ptr<Converter>(new Mix(bufferSize, firstParameter, secondParameter));
        }

        case MY_NAME_CONV: // FIXME later.
        {
//            return std::shared_ptr<Converter>(new Randomizer(bufferSize, firstParameter, secondParameter));
        }

        default:
        {
            break;
        }
    }
}
