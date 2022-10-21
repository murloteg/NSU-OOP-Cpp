#include <iostream>
#include <vector.h>

using namespace std;

int main()
{
    {
        Vector firstVector(10);
        cout << firstVector.GetSize() << "\n";
    }

    auto secondVector = new Vector(5);
    cout << secondVector->GetSize() << "\n";
    delete secondVector;

    return 0;
}
