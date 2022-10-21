#include "MyClass.h"

MyClass::MyClass(int size)
{
    this->array_ = new int[size];
    this->size_ = size;

    for (int i = 0; i < size_; ++i)
    {
        this->array_[i] = 0;
    }

    cout << "Object was created!" << '\n';
}

int MyClass::GetSize() const
{
    return size_;
}

void MyClass::Print()
{
    for (int i = 0; i < GetSize(); ++i)
    {
        cout << array_[i] << ' ';
    }
    cout << '\n';
}

void MyClass::Update(MyClass &object) const
{
    for (int i = 0; i < GetSize(); ++i)
    {
        cout << "Input " << i + 1 << " value:" << '\n';
        int value = 0;
        cin >> value;
        object.array_[i] = value;
    }
}

MyClass::~MyClass()
{
    delete[] array_;
    cout << '\n' << "Object was deleted!" << '\n';
}
