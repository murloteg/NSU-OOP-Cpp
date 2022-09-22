#include "BigInt.h"

BigInt::BigInt()
{
}

BigInt::BigInt(int value)
{
    int length = 0;
    int tempValue = value;
    while (tempValue > 0)
    {
        ++length;
        tempValue /= 10;
    }

    int realSize = (length / 3) + 1 * (length % 3 != 0);
    for (size_t i = 0; i < realSize; ++i)
    {
        int nextPart = value % BASE;
        this->vector_.push_back(nextPart);
        value /= BASE;
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
}

BigInt::BigInt(const BigInt &origin)
{
    for (size_t i = 0; i < origin.size(); ++i)
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

BigInt& BigInt::operator=(const BigInt& other)
{
    this->vector_ = other.vector_;
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
    for (size_t i = 0; i < std::max(this->size(), other.size()) || carry; ++i)
    {
        if (i == this->size())
        {
            this->vector_.push_back(0);
        }

        this->vector_[i] += carry + ((i < other.size()) ? other.vector_[i] : 0);
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
    int carry = 0;
    for (size_t i = 0; i < std::max(this->size(), other.size()) || carry; ++i)
    {
        this->vector_[i] -= ((i < other.size()) ? other.vector_[i] : 0);
        carry = (this->vector_[i] < 0);
        if (carry)
        {
            this->vector_[i] += BASE;
            this->vector_.at(i + 1) -= 1;
        }
    }

    while (!this->vector_.empty() && this->vector_.back() == 0)
    {
        this->vector_.pop_back();
    }

    return *this;
}

BigInt& BigInt::operator*=(const BigInt &other)
{
    size_t sizeOfFirst = this->size();
    BigInt tempValue(*this);
    this->vector_.resize(sizeOfFirst + other.size());
    for (int i = 0; i < sizeOfFirst; ++i)
    {
        this->vector_[i] = 0;
    }

    for (size_t i = 0; i < sizeOfFirst; ++i)
    {
        int carry = 0;
        for (int j = 0; j < other.size() || carry; ++j)
        {
            long long int partialResult = this->vector_[i + j] + carry + tempValue.vector_[i] * other.vector_[j];
            this->vector_[i + j] = static_cast<int> (partialResult % BASE);
            carry = static_cast<int> (partialResult / BASE);
        }
    }

    while(!this->vector_.empty() && this->vector_.back() == 0)
    {
        this->vector_.pop_back();
    }

    return *this;
}

BigInt operator+(const BigInt& first, const BigInt& second)
{
    for (size_t i = 0; i < std::max(first.size(), second.size()); ++i)
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
