#include "Factory.h"

Converter &Factory::createConverter(std::string name, unsigned int firstParameter, unsigned int secondParameter)
{
    auto converterName = converters.find(name);
    switch (converterName->second)
    {
        // TODO: finish this block.
        case MUTE:
        {

            break;
        }

        case MIX:
        {
            break;
        }

        case MY_NAME_CONV: // FIXME later.
        {
            break;
        }

        default:
        {
            break;
        }
    }
}
