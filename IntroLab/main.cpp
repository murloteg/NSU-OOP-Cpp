#include <iostream>
#include "module1.h"
#include "module2.h"
#include "module3.h"

/* для написания cout вместо std::cout необходимо использовать
 * пространство имён std.
 */
int main(int argc, char** argv)
{
    std::cout <<  "Hello world!" << "\n";

    std::cout << Module1::getMyName() << "\n";
    std::cout << Module2::getMyName() << "\n";

    using namespace Module1;

    /* Будет выведено "John" */
    std::cout << getMyName() << "\n"; // (A)
    std::cout << Module2::getMyName() << "\n";

    /* Если убрать комментарии, то произойдет ошибка из-за определения ф-ии getMyName
     * сразу в двух пространствах имён и попытке их одновременного использования.
     * Можно в явном виде прописывать, из какого пространства имён должна
     * использоваться данная функция. Например, Module1::getMyName().
     */

    //using namespace Module2; // (B)
    //std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

    using Module2::getMyName;

    /* Будет выведено "James" */
    std::cout << getMyName() << "\n"; // (D)
    /* Будет выведено "Peter" */
    std::cout << Module3::getMyName() << "\n";
}
