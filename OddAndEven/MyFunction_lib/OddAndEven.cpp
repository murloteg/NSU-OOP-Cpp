#include "OddAndEven.h"

void GetNumberOfOddAndEven(int first, int second)
{
    int max = std::max(first, second);
    int min = std::min(first, second);
    int result = ((max + min) - 2 * (min - 1)) / 2;
    if (first % 2 == 0 && second % 2 == 0)
    {
        IS_NUMBER_OF_EVEN;
        cout << result << endl;
    }

    else if (first % 2 != 0 && second % 2 !=0)
    {
        IS_NUMBER_OF_ODD;
        cout << result << endl;
    }

    else
    {
        IS_NUMBER_OF_BOTH;
        cout << result << endl;
    }
}
