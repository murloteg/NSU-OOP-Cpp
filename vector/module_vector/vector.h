#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H
#include <iostream>

class Vector
{
private:
    double* elem_;
    int size_;

public:
    Vector(int size);
    int GetSize() const;
    friend Vector operator+(const Vector &firstVector, const Vector &secondVector);
    friend Vector operator*(const Vector &firstVector, const Vector &secondVector);
    double &operator[](int index);
    Vector(std::initializer_list<double> lst);
    ~Vector();
};


#endif //VECTOR_VECTOR_H
