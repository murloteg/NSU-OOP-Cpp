#include "ConverterFactory.h"

Converter* ConverterFactory::createConverter(std::string nameOfConverter, std::string wavFileName, unsigned int firstParameter, unsigned int secondParameter)
{
    auto converterName = converters.find(nameOfConverter);
    switch (converterName->second)
    {
        // TODO: finish this block.
        case MUTE:
        {
            return new Mute(wavFileName, firstParameter, secondParameter);
        }

        case MIX:
        {
            break;
        }

        case MY_NAME_CONV: // FIXME later.
        {
            return new Randomizer(wavFileName, firstParameter, secondParameter);
        }

        default:
        {
            break;
        }
    }
}
