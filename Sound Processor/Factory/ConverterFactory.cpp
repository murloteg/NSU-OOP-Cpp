#include "ConverterFactory.h"

Converter* ConverterFactory::createConverter(std::string nameOfConverter, int bufferSize,
                                             unsigned int firstParameter, unsigned int secondParameter)
{
    auto converterName = converters.find(nameOfConverter);
    switch (converterName->second)
    {
        // TODO: finish this block.
        case MUTE:
        {
            return new Mute(bufferSize, firstParameter, secondParameter);
        }

        case MIX:
        {
            break;
        }

        case MY_NAME_CONV: // FIXME later.
        {
//            return new Randomizer(currentWAV, firstParameter, secondParameter);
        }

        default:
        {
            break;
        }
    }
}
