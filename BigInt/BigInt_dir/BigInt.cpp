#include "BigInt.h"

BigInt::BigInt()
{

}

BigInt::BigInt(int value)
{
    if (value < 0)
    {
        this->sign_ = true;
    }

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

    this->DeleteZeros();
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

void BigInt::DeleteZeros()
{
    while (!this->vector_.empty() && this->vector_.back() == 0)
    {
        this->vector_.pop_back();
    }
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

    this->DeleteZeros();
    return *this;
}

BigInt& BigInt::operator*=(const BigInt &other)
{
    size_t sizeOfFirst = this->size();
    BigInt tempValue(*this);
    this->vector_.resize(sizeOfFirst + other.size());
    for (int i = 0; i < this->size(); ++i)
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

    this->DeleteZeros();
    return *this;
}

BigInt &BigInt::operator/=(const BigInt &other)
{
    // exception: division by zero.

    if (other.size() == 1)
    {
        int carry = 0;
        for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
        {
            long long int partialResult = this->vector_[i] + carry * BASE;
            this->vector_[i] = static_cast<int> (partialResult / other.vector_.back());
            carry = static_cast<int> (partialResult % other.vector_.back());
        }

        this->DeleteZeros();
        return *this;
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
        char fillChar = output.fill('0');
        for (int i = static_cast<int> (value.size() - 2); i >= 0; --i)
        {
            output << std::setw(3) << value.vector_[i];
        }
        output.fill(fillChar);
    }

    return output;
}

BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt temp(*this);
    temp.sign_ = !temp.sign_;
    return temp;
}

bool BigInt::operator==(const BigInt &other)
{
    if (this->size() != other.size())
    {
        return false;
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        if (this->vector_[i] != other.vector_[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(const BigInt &other)
{
    if (this->size() != other.size())
    {
        return true;
    }

    bool status = false;
    for (size_t i = 0; i < this->size(); ++i)
    {
        if (this->vector_[i] != other.vector_[i])
        {
            status = true;
        }
    }

    return status;
}

bool BigInt::operator<(const BigInt &other)
{
    if (this->size() < other.size())
    {
        return true;
    }

    else if (this->size() > other.size() || (*this == other))
    {
        return false;
    }

    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        if (this->vector_[i] > other.vector_[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator>(const BigInt &other)
{
    if (this->size() > other.size())
    {
        return true;
    }

    else if (this->size() < other.size() || (*this == other))
    {
        return false;
    }

    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        if (this->vector_[i] < other.vector_[i])
        {
            return false;
        }
    }

    return true;
}

bool BigInt::operator<=(const BigInt &other)
{
    return (*this < other || *this == other);
}

bool BigInt::operator>=(const BigInt &other)
{
    return (*this > other || *this == other);
}

BigInt operator+(const BigInt& first, const BigInt& second)
{
    BigInt temp = BigInt(first);
    temp += second;
    return temp;
}

BigInt operator-(const BigInt &first, const BigInt &second)
{
    BigInt temp = BigInt(first);
    temp -= second;
    return temp;
}

BigInt operator*(const BigInt &first, const BigInt &second)
{
    BigInt temp = BigInt(first);
    temp *= second;
    return temp;
}
