#include <MyClass.h>

using namespace std;

int main()
{
    int size = 0;
    cin >> size;
    MyClass object = MyClass(size);

    object.MyClass::Print();
    object.Update(object);
    object.Print();

    return 0;
}
