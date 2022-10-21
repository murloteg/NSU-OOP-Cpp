#include "vector.h"

using namespace std;

Vector::Vector(int size)
{
    this->elem_ = new double[size];
    this->size_ = size;
    cout << "vector created!\n";
}

int Vector::GetSize() const
{
    return this->size_;
}

Vector::~Vector()
{
    delete[] this->elem_;
    cout << "vector deleted!\n";
}

Vector operator+(const Vector &firstVector, const Vector &secondVector)
{
    int maxSize = (firstVector.GetSize() > secondVector.GetSize() ? firstVector.GetSize() : secondVector.GetSize());
    Vector newVector = Vector(maxSize);
    for (int i = 0; i < maxSize; ++i)
    {
        newVector.elem_[i] = firstVector.elem_[i] + secondVector.elem_[i];
    }

    return newVector;
}

Vector operator*(const Vector &firstVector, const Vector &secondVector)
{
    int maxSize = (firstVector.GetSize() > secondVector.GetSize() ? firstVector.GetSize() : secondVector.GetSize());
    Vector newVector = Vector(maxSize);
    for (int i = 0; i < maxSize; ++i)
    {
        newVector.elem_[i] = firstVector.elem_[i] * secondVector.elem_[i];
    }

    return newVector;
}

double &Vector::operator[](int index)
{
    return this->elem_[index];
}


Vector::Vector(std::initializer_list<double> lst):
        elem_(new double[lst.size()]),
        size_(static_cast<int>(lst.size())) {
    std::copy(lst.begin(), lst.end(), elem_);
}
