#include "BigInt.h"

BigInt::BigInt()
{
    this->size_ = this->vector_.size();
}

BigInt::BigInt(int size)
{
    this->size_ = size;
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->vector_.push_back(0);
    }
}

BigInt::BigInt(std::string string)
{
    int indexInVector = 0;
    for (int i = static_cast<int> (string.length()); i > 0; i -= 3)
    {
        if (i > 3)
        {
            this->vector_.push_back(atoi(string.substr(i - 3, 3).c_str()));
            ++indexInVector;
        }

        else
        {
            this->vector_.push_back(atoi(string.substr(0, i).c_str()));
            ++indexInVector;
        }
    }

    while (!this->vector_.empty() && this->vector_.back() == 0)
    {
        this->vector_.pop_back();
    }

    this->size_ = this->vector_.size();
}

BigInt::BigInt(const BigInt &origin)
{
    this->size_ = origin.size();
    for (size_t i = 0; i < this->size_; ++i)
    {
        this->vector_.push_back(origin.vector_[i]);
    }
}

BigInt::~BigInt()
{
    this->vector_.clear();
}

size_t BigInt::size() const
{
    return this->vector_.size();
}

int BigInt::operator[](int index)
{
    return this->vector_[index];
}

BigInt& BigInt::operator=(const BigInt& other)
{
    this->vector_ = other.vector_;
    this->size_ = other.size_;
    return *this;
}

BigInt BigInt::operator~() const
{

}

BigInt& BigInt::operator++()
{

}

const BigInt BigInt::operator++(int) const
{

}

BigInt& BigInt::operator--()
{

}

const BigInt BigInt::operator--(int) const
{

}

BigInt& BigInt::operator+=(const BigInt &other)
{
    int carry = 0;
    for (size_t i = 0; i < std::max(this->vector_.size(), other.vector_.size()) || carry; ++i)
    {
        if (i == this->vector_.size())
        {
            this->vector_.push_back(0);
        }

        this->vector_[i] += carry + ((i < other.vector_.size()) ? other.vector_[i] : 0);
        carry = (this->vector_[i] >= BASE);
        if (carry)
        {
            this->vector_[i] -= BASE;
        }
    }

    return *this;
}

BigInt& BigInt::operator-=(const BigInt &other)
{

}

BigInt operator+(const BigInt& first, const BigInt& second)
{
    size_t maxSize = (first.size() > second.size() ? first.size() : second.size());
    BigInt tempVector(maxSize);

    for (size_t i = 0; i < maxSize; ++i)
    {
        // update later with using "+=".
    }
}

std::ostream& operator<<(std::ostream &output, const BigInt &value)
{
    if (value.size() == 0)
    {
        output << 0;
    }

    else
    {
        output << value.vector_.back();
        for (int i = value.size() - 2; i >= 0; --i)
        {
            output << std::setw(3) << value.vector_[i];
        }

        output.fill('0');
    }

    return output;
}
