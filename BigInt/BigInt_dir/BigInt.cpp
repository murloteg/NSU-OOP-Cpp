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
    if (string.size() == 0)
    {
        this->sign_ = false;
    }

    else
    {
        if (string[0] == '-')
        {
            string = string.substr(1);
            this->sign_ = true;
        }
        else
        {
            this->sign_ = false;
        }

        for (int i = static_cast<int> (string.length()); i > 0; i -= 3)
        {
            if (i > 3)
            {
                this->vector_.push_back(static_cast<int> (strtol(string.substr(i - 3, 3).c_str(), nullptr, 10)));
                ++indexInVector;
            }

            else
            {
                this->vector_.push_back(static_cast<int> (strtol(string.substr(0, i).c_str(), nullptr, 10)));
                ++indexInVector;
            }
        }
    }


    this->DeleteZeros();
}

BigInt::BigInt(const BigInt &origin)
{
    this->sign_ = origin.sign_;
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

bool BigInt::IsEqualsZero(const BigInt& object)
{
    if (this->size() == 0)
    {
        return true;
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        if (this->vector_[i] != 0)
        {
            return false;
        }
    }

    return true;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    this->vector_.clear();
    for (size_t i = 0; i < other.size(); ++i)
    {
        this->vector_.push_back(other.vector_[i]);
    }

    return *this;
}

BigInt BigInt::operator~() const
{

}

BigInt& BigInt::operator++()
{
    (*this) += 1;
    return *this;
}

const BigInt BigInt::operator++(int)
{
    BigInt temp(*this);
    (*this) += 1;
    return temp;
}

BigInt& BigInt::operator--()
{
    (*this) -= 1;
    return *this;
}

const BigInt BigInt::operator--(int)
{
    BigInt temp(*this);
    (*this) -= 1;
    return temp;
}

BigInt& BigInt::operator+=(const BigInt &other)
{
    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_ || this->sign_ && other.sign_)
    {
        BigInt bigger(GetBigger(*this, other));
        BigInt lower(GetLower(*this, other));

        if (!bigger.sign_ && lower.sign_)
        {
            lower.sign_ = false;
            *this = (bigger - lower);
            this->sign_ = false;
        }

        else if (bigger.sign_ && lower.sign_)
        {
            lower.sign_ = false;
            bigger.sign_ = false;
            *this = -(bigger + lower);
            this->sign_ = true;
        }

        else if (bigger.sign_ && !lower.sign_)
        {
            bigger.sign_ = false;
            *this = -(bigger - lower);
        }

        return *this;
    }

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
    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_ || this->sign_ && other.sign_)
    {
        BigInt bigger(GetBigger(*this, other));
        BigInt lower(GetLower(*this, other));
        if (lower.sign_ && bigger.sign_)
        {
            if (bigger == *this)
            {
                lower.sign_ = false;
                bigger.sign_ = false;
                this->sign_ = false;
                *this = (lower - bigger);
            }

            else if (bigger == other)
            {
                lower.sign_ = false;
                bigger.sign_ = false;
                this->sign_ = true;
                *this = -(lower - bigger);
            }
        }

        else if (lower.sign_ && !bigger.sign_)
        {
            lower.sign_ = false;
            this->sign_ = false;
            *this = (bigger + lower);
        }

        else if (!lower.sign_ && bigger.sign_)
        {
            bigger.sign_ = false;
            this->sign_ = true;
            *this = (bigger + lower);
        }

        return *this;
    }

    if (this->size() < other.size())
    {
        *this = (other - *this);
        return (*this);
    }

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
    if (this->sign_ && !other.sign_)
    {
        this->sign_ = false;
        *this = (*this * other);
        this->sign_ = true;
        return *this;
    }

    else if (!this->sign_ && other.sign_)
    {
        BigInt temp(other);
        temp.sign_ = false;
        *this = (*this * temp);
        this->sign_ = true;
        return *this;
    }

    else if (this->sign_ && other.sign_)
    {
        this->sign_ = false;
        BigInt temp(other);
        temp.sign_ = false;
        *this = (*this * temp);
    }

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

BigInt BigInt::BinarySearch(const BigInt &remainder, const BigInt &other)
{
    int leftValue = 0;
    int rightValue = BASE;
    int middleValue;
    BigInt result(0);
    while (leftValue <= rightValue)
    {
        middleValue = (leftValue + rightValue) / 2;
        result = middleValue;
        if (remainder == result * other)
        {
            break;
        }

        (remainder > result * other) ? leftValue = middleValue + 1 : rightValue = middleValue - 1;
    }

    while (remainder < (result * other))
    {
        result -= 1;
    }

    return result;
}

BigInt& BigInt::operator/=(const BigInt &other)
{
    // exception: division by zero.
    const BigInt& tempValue(other);
    BigInt remainder(0);
    BigInt result(0);
    BigInt partialResult(0);
    BigInt objectOfBase(BASE);
    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        partialResult = objectOfBase * remainder;
        remainder = this->vector_[i];
        remainder += partialResult;
        partialResult = remainder;
        remainder = BinarySearch(remainder, tempValue);
        result *= objectOfBase;
        result += remainder;
        if (IsEqualsZero(remainder))
        {
            remainder = this->vector_[i];
        }

        else
        {
            remainder = partialResult - (tempValue * remainder);
        }
    }

    this->vector_.clear();
    this->vector_ = result.vector_;
    return *this;
}

BigInt& BigInt::operator%=(const BigInt &other)
{
    BigInt temp(*this);
    temp /= other;
    *this = (*this - temp * other);
    return *this;
}

BigInt& BigInt::operator^=(const BigInt &other) // XOR
{

}

std::ostream& operator<<(std::ostream &output, const BigInt &value)
{
    if (value.size() == 0)
    {
        output << 0;
    }

    else
    {
        if (value.sign_)
        {
            output << '-';
        }

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

BigInt::operator int() const
{
    int result = 0;
    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        result = result * BASE + this->vector_[i];
    }

    return result;
}

BigInt BigInt::GetBigger(const BigInt &first, const BigInt &second)
{
    return (first >= second) ? first : second;
}

BigInt BigInt::GetLower(const BigInt &first, const BigInt &second)
{
    return (first < second) ? first : second;
}

BigInt operator+(const BigInt& first, const BigInt& second)
{
    BigInt temp(first);
    temp += second;
    return temp;
}

BigInt operator-(const BigInt &first, const BigInt &second)
{
    BigInt temp(first);
    temp -= second;
    return temp;
}

BigInt operator*(const BigInt &first, const BigInt &second)
{
    BigInt temp(first);
    temp *= second;
    return temp;
}

BigInt operator/(const BigInt &first, const BigInt &second)
{
    BigInt temp(first);
    temp /= second;
    return temp;
}

BigInt operator%(const BigInt &first, const BigInt &second)
{
    BigInt temp(first);
    temp %= second;
    return temp;
}
