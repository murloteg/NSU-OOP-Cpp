#ifndef HOMEWORK_CPP_MYCLASS_H
#define HOMEWORK_CPP_MYCLASS_H
#include <iostream>

using namespace std;

class MyClass
{
private:
    int size_;
    int* array_;

public:
    MyClass(int size);
    int GetSize() const;
    void Print();
    void Update(MyClass &object) const;
    ~MyClass();
};


#endif //HOMEWORK_CPP_MYCLASS_H
