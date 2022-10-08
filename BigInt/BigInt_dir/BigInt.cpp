#include "BigInt.h"

BigInt::BigInt()
{
    this->sign_ = false;
    this->vector_.push_back(0);
}

BigInt::BigInt(int value) 
{
    bool overflowStatus = false;
    if (value < 0)
    {
        this->sign_ = true;
        if (value == INT_MIN)
        {
            value += 1;
            overflowStatus = true;
        }

        value *= (-1);
    }

    else
    {
        this->sign_ = false;
    }

    if (value == 0)
    {
        this->vector_.push_back(0);
        return;
    }

    int length = 0;
    int tempValue = value;
    while (tempValue > 0)
    {
        ++length;
        tempValue /= 10;
    }

    int realSize = (length / getLengthOfBase()) + 1 * (length % getLengthOfBase() != 0);
    for (size_t i = 0; i < realSize; ++i)
    {
        int nextPart = value % BASE;
        this->vector_.push_back(nextPart);
        value /= BASE;
    }

    if (overflowStatus)
    {
        ++this->vector_[0];
    }
}

BigInt::BigInt(std::string string)
{
    int indexInVector = 0;
    bool isNormalString = false;
    for (char i : string)
    {
        if (i >= '0' && i <= '9')
        {
            isNormalString = true;
            break;
        }
    }

    if (string.empty() || !isNormalString)
    {
        throw std::invalid_argument("bad value");
    }

    else
    {
        bool isZero = true;
        for (int i = 1; i < string.length(); ++i)
        {
            if (string[i] != '0')
            {
                isZero = false;
                break;
            }
        }

        if (string[0] == '-' && !isZero)
        {
            string = string.substr(1);
            this->sign_ = true;
        }

        else
        {
            this->sign_ = false;
        }

        for (int i = static_cast<int> (string.length()); i > 0; i -= getLengthOfBase())
        {
            if (i > getLengthOfBase())
            {
                this->vector_.push_back(static_cast<int> (strtol(string.substr(i - getLengthOfBase(), getLengthOfBase()).c_str(), nullptr, 10)));
                ++indexInVector;
            }

            else
            {
                this->vector_.push_back(static_cast<int> (strtol(string.substr(0, i).c_str(), nullptr, 10)));
                ++indexInVector;
            }
        }
    }

    this->deleteZeros();
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

int BigInt::getLengthOfBase()
{
    int length = 0;
    int base = BASE;
    while (base > 0)
    {
        base /= 10;
        ++length;
    }

    --length;
    return length;
}

std::string BigInt::getZeroStringForBase()
{
    std::string zeroString;
    for (int i = 0; i < getLengthOfBase(); ++i)
    {
        zeroString += '0';
    }

    return zeroString;
}

void BigInt::deleteZeros()
{
    while (!this->vector_.empty() && this->vector_.back() == 0)
    {
        if (this->size() == 1)
        {
            return;
        }

        this->vector_.pop_back();
    }
}

bool BigInt::isEqualsZero(const BigInt& object)
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

void BigInt::convertToBinaryString()
{
    this->binaryNotation = "";
    BigInt two(2);
    while (!isEqualsZero(*this))
    {
        int result = *this % two;
        if (result == 0)
        {
            this->binaryNotation += "0";
        }

        else
        {
            this->binaryNotation += "1";
        }
        *this /= two;
    }
    std::reverse(binaryNotation.begin(), binaryNotation.end());
}

int BigInt::getNumberOfZerosFromCell(int value)
{
    int numberOfZeros = 0;
    int base = BASE;
    while (base > 1)
    {
        base /= 10;
        ++numberOfZeros;
    }

    int tempBase = 1;
    while (value >= tempBase && tempBase < BASE)
    {
        tempBase *= 10;
        --numberOfZeros;
    }

    return numberOfZeros;
}

void BigInt::swap(BigInt& first, BigInt& second)
{
    BigInt tempValue(first);
    first = second;
    second = tempValue;
}

bool BigInt::checkSign()
{
    if (isEqualsZero(*this))
    {
        return false;
    }

    return this->sign_;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (*this == other)
    {
        return *this;
    }

    this->vector_.clear();
    this->sign_ = other.sign_;
    for (size_t i = 0; i < other.size(); ++i)
    {
        this->vector_.push_back(other.vector_[i]);
    }

    return *this;
}

BigInt BigInt::operator~() const
{
    BigInt tempValue(*this);
    tempValue += 1;
    tempValue.sign_ = !tempValue.sign_;
    return tempValue;
}

BigInt& BigInt::operator++()
{
    (*this) += 1;
    return *this;
}

const BigInt BigInt::operator++(int)
{
    BigInt tempValue(*this);
    ++(*this);
    return tempValue;
}

BigInt& BigInt::operator--()
{
    if (!this->sign_)
    {
        if (isEqualsZero(*this))
        {
            this->vector_[0] = 1;
            this->sign_ = true;
            return *this;
        }

        if (this->size() == 1)
        {
            --this->vector_[0];
            return *this;
        }

        --this->vector_[0];
        for (int i = 0; i < this->size() - 1; ++i)
        {
            if (this->vector_[i] < 0)
            {
                this->vector_[i] = (BASE + this->vector_[i]);
                this->vector_[i + 1] -= 1;
            }
        }
    }

    else
    {
        if (this->size() == 1)
        {
            ++this->vector_[0];
            if (this->vector_[0] == BASE)
            {
                this->vector_.resize(2);
                this->vector_[0] = 0;
                this->vector_[1] = 1;
            }

            return *this;
        }

        ++this->vector_[0];
        for (int i = 0; i < this->size() - 1; ++i)
        {
            if (this->vector_[i] >= BASE)
            {
                this->vector_[i] = 0;
                this->vector_[i + 1] -= 1;
            }
        }
    }

    deleteZeros();
    return *this;
}

const BigInt BigInt::operator--(int)
{
    BigInt tempValue(*this);
    --(*this);
    return tempValue;
}

BigInt& BigInt::operator+=(const BigInt &other)
{
    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_ || this->sign_ && other.sign_)
    {
        BigInt bigger(getBigger(*this, other));
        BigInt lower(getLower(*this, other));
        if (bigger.sign_ && lower.sign_)
        {
            bigger.sign_ = lower.sign_ = false;
            *this = -(bigger + lower);
            return *this;
        }

        else if (!bigger.sign_ && lower.sign_)
        {
            lower.sign_ = false;
            *this = bigger - lower;
            return *this;
        }
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
    if (isEqualsZero(*this))
    {
        BigInt tempValue(other);
        if (isEqualsZero(tempValue))
        {
            tempValue.sign_ = true;
        }

        *this = -tempValue;
        return *this;
    }

    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_ || this->sign_ && other.sign_)
    {
        BigInt bigger(getBigger(*this, other));
        BigInt lower(getLower(*this, other));
        bool firstIsBigger = (bigger == *this);
        if (lower.sign_ && bigger.sign_)
        {
            lower.sign_ = bigger.sign_ = false;
            *this = (firstIsBigger) ? lower - bigger: -(lower - bigger);
            return *this;
        }

        else if (lower.sign_ && !bigger.sign_)
        {
            lower.sign_ = false;
            *this = (firstIsBigger) ? lower + bigger: -(lower + bigger);
            return *this;
        }
    }

    if (*this < other)
    {
        *this = -(other - *this);
        return *this;
    }

    BigInt result(*this);
    int carry = 0;
    for (size_t i = 0; i < result.size(); ++i)
    {
        result.vector_[i] -= ((i < other.size()) ? other.vector_[i] : 0) + carry;
        if (result.vector_[i] < 0)
        {
            result.vector_[i] += BASE;
            --result.vector_[i + 1];
        }
    }

    *this = result;
    deleteZeros();
    return *this;
}

BigInt &BigInt::divideBy2(BigInt& value)
{
    int carry = 0;
    int length = static_cast<int> (value.size());
    int tempValue;
    while (length > 0)
    {
        tempValue = value.vector_[length - 1] + carry * BASE;
        value.vector_[length - 1] = tempValue / 2;
        carry = tempValue % 2;
        --length;
    }

    *this = value;
    return *this;
}

int BigInt::getRemainderBy2(BigInt& value)
{
    if (value.size() == 0 || value.vector_[0] % 2 == 0)
    {
        return 0;
    }

    return 1;
}

BigInt& BigInt::operator*=(const BigInt &other) // first * second = 2^n + q
{
    BigInt result(0);
    BigInt first(*this);
    BigInt second(other);

    bool sign = false;
    if (this->sign_ != second.sign_)
    {
        sign = true;
    }

    first.sign_ = second.sign_ = false;
    if (isEqualsZero(first) || isEqualsZero(second))
    {
        *this = 0;
        return *this;
    }

    if (first.size() < second.size())
    {
        swap(first, second);
    }

    while (second > static_cast<BigInt> (0))
    {
        if (getRemainderBy2(second) == 0)
        {
            first = first + first;
            second = divideBy2(second);
        }

        else
        {
            second -= 1;
            result += first;
        }
    }

    *this = result;
    this->sign_ = sign;
    return *this;
}

BigInt& BigInt::operator/=(const BigInt &other)
{
    BigInt result(0);
    bool sign = false;
    BigInt first(*this);
    BigInt second(other);
    if (isEqualsZero(other))
    {
        throw std::invalid_argument("division by zero");
    }

    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_)
    {
        sign = true;
    }

    first.sign_ = second.sign_ = false;
    BigInt currentValue(0);
    for (int i = static_cast<int> (first.size() - 1); i >= 0; --i)
    {
        currentValue *= BASE;
        currentValue.vector_[0] = first.vector_[i];

        int currentDivider = 0;
        int leftValue = 0;
        int rightValue = BASE;
        BigInt middleValue(0);
        BigInt temporaryValue(0);
        while (leftValue <= rightValue)
        {
            int middle = (leftValue + rightValue) / 2;
            middleValue = middle;
            temporaryValue = middleValue * second;
            if (temporaryValue <= currentValue)
            {
                currentDivider = middle;
                leftValue = middle + 1;
            }

            else
            {
                rightValue = middle - 1;
            }
        }

        result *= BASE;
        result += currentDivider;
        BigInt currDivObject(currentDivider);
        currentValue = currentValue - second * currDivObject;
    }

    *this = result;
    this->sign_ = sign;
    deleteZeros();
    return *this;
}

BigInt& BigInt::operator%=(const BigInt &other)
{
    BigInt tempValue(*this);
    BigInt second(other);
    this->sign_ = tempValue.sign_ = second.sign_ = false;
    tempValue /= second;
    *this = (*this - tempValue * second);
    return *this;
}

void BigInt::addMoreZeros(std::string &string, int count)
{
    std::reverse(string.begin(), string.end());
    for (int i = 0; i < count; ++i)
    {
        string += "0";
    }
    std::reverse(string.begin(), string.end());
}

BigInt BigInt::convertFromBinaryNotation(std::string &string)
{
    int realSize = static_cast<int> (string.length() / BIT_LENGTH);
    BigInt result(0);
    result.vector_.resize(realSize);
    BigInt tempValue(1);
    int indexInString = 0;
    int remainderOfStringLength = static_cast<int> (string.length() % BIT_LENGTH);
    if (remainderOfStringLength != 0)
    {
        for (int j = 0; j < remainderOfStringLength; ++j)
        {
            result += (string[(realSize * BIT_LENGTH + remainderOfStringLength - 1) - j] == '0') ? static_cast<BigInt> (0) : tempValue;
            tempValue *= 2;
        }
    }

    for (int i = 0; i < realSize; ++i)
    {
        indexInString = (realSize == 1) ? MAX_BIT_INDEX : BIT_LENGTH * (realSize - i) - 1;
        for (int j = 0; j < BIT_LENGTH; ++j)
        {
            result += (string[indexInString - j] == '0') ? static_cast<BigInt> (0) : tempValue;
            tempValue *= 2;
        }
    }

    return result;
}

int BigInt::prepareStringsAndGetMaxLength(std::string& first, std::string& second)
{
    int maxLength = static_cast<int> (std::max(first.length(), second.length()));
    if (first.length() != maxLength || first.length() < BIT_LENGTH)
    {
        addMoreZeros(first, static_cast<int> (maxLength - first.length()));
    }

    else if (second.length() != maxLength || second.length() < BIT_LENGTH)
    {
        addMoreZeros(second, static_cast<int> (maxLength - second.length()));
    }

    if (first.length() <= BIT_LENGTH && second.length() <= BIT_LENGTH)
    {
        addMoreZeros(first, static_cast<int> (BIT_LENGTH - first.length()));
        addMoreZeros(second, static_cast<int> (BIT_LENGTH - second.length()));
        maxLength = BIT_LENGTH;
    }

    return maxLength;
}

BigInt BigInt::bitwiseXOR(std::string& first, std::string& second)
{
    std::string result;
    int maxLength = prepareStringsAndGetMaxLength(first, second);
    for (int i = 0; i < maxLength; ++i)
    {
        result += (first[i] == second[i]) ? "0" : "1";
    }

    BigInt tempValue = convertFromBinaryNotation(result);
    tempValue.deleteZeros();
    return tempValue;
}

BigInt& BigInt::operator^=(const BigInt &other)
{
    bool sign = (this->sign_ != other.sign_);
    BigInt second(other);
    this->sign_ = second.sign_ = false;
    this->convertToBinaryString();
    second.convertToBinaryString();
    *this = bitwiseXOR(this->binaryNotation, second.binaryNotation);
    this->sign_ = sign;
    this->sign_ = checkSign();
    return *this;
}

BigInt BigInt::bitwiseAND(std::string& first, std::string& second)
{
    std::string result;
    int maxLength = prepareStringsAndGetMaxLength(first, second);
    for (int i = 0; i < maxLength; ++i)
    {
        result += (first[i] == '1' && second[i] == '1') ? "1" : "0";
    }

    BigInt tempValue = convertFromBinaryNotation(result);
    tempValue.deleteZeros();
    return tempValue;
}

BigInt &BigInt::operator&=(const BigInt &other)
{
    bool sign = (this->sign_ == other.sign_) && this->sign_ && other.sign_;
    BigInt second(other);
    this->sign_ = second.sign_ = false;
    this->convertToBinaryString();
    second.convertToBinaryString();
    *this = bitwiseAND(this->binaryNotation, second.binaryNotation);
    this->sign_ = sign;
    this->sign_ = checkSign();
    return *this;
}

BigInt BigInt::bitwiseOR(std::string& first, std::string& second)
{
    std::string result;
    int maxLength = prepareStringsAndGetMaxLength(first, second);
    for (int i = 0; i < maxLength; ++i)
    {
        result += (first[i] == '1' || second[i] == '1') ? '1' : '0';
    }

    BigInt tempValue = convertFromBinaryNotation(result);
    tempValue.deleteZeros();
    return tempValue;
}

BigInt &BigInt::operator|=(const BigInt &other)
{
    bool sign = (this->sign_ != other.sign_) || (this->sign_ && other.sign_);
    BigInt second(other);
    this->sign_ = second.sign_ = false;
    this->convertToBinaryString();
    second.convertToBinaryString();
    *this = bitwiseOR(this->binaryNotation, second.binaryNotation);
    this->sign_ = sign;
    this->sign_ = checkSign();
    return *this;
}

std::ostream& operator<<(std::ostream &output, const BigInt &value)
{
    output << (std::string) value;
    return output;
}

BigInt BigInt::operator+() const
{
    return *this;
}

BigInt BigInt::operator-() const
{
    BigInt tempValue(*this);
    tempValue.sign_ = !tempValue.sign_;
    return tempValue;
}

bool BigInt::operator==(const BigInt &other)
{
    if (this->size() != other.size() || this->sign_ != other.sign_)
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
    return !(*this == other);
}

bool BigInt::operator<(const BigInt &other)
{
    if (this->sign_ && !other.sign_)
    {
        return true;
    }

    else if (!this->sign_ && other.sign_)
    {
        return false;
    }

    else if (this->sign_ && other.sign_)
    {
        BigInt first(*this);
        BigInt second(other);
        first.sign_ = second.sign_ = false;
        return !(first < second);
    }

    if (this->size() != other.size())
    {
        return (this->size() < other.size());
    }

    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        if (this->vector_[i] != other.vector_[i])
        {
            return (this->vector_[i] < other.vector_[i]);
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt &other)
{
    if (this->sign_ && !other.sign_)
    {
        return false;
    }

    else if (!this->sign_ && other.sign_)
    {
        return true;
    }

    else if (this->sign_ && other.sign_)
    {
        BigInt first(*this);
        BigInt second(other);
        first.sign_ = second.sign_ = false;
        return !(first > second);
    }

    if (this->size() != other.size())
    {
        return (this->size() > other.size());
    }

    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
       if (this->vector_[i] != other.vector_[i])
       {
           return (this->vector_[i] > other.vector_[i]);
       }
    }

    return false;
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
    bool isOverflow = false;
    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        if (result < 0)
        {
            isOverflow = true;
            break;
        }
        result = result * BASE + this->vector_[i];
    }

    if (isOverflow)
    {
        throw std::length_error("overflow for int type");
    }

    return result;
}

BigInt::operator std::string() const
{
    std::string string;
    if (this->sign_)
    {
        string += "-";
    }

    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        int numberOfZeros = getNumberOfZerosFromCell(this->vector_[i]);
        if (numberOfZeros == getLengthOfBase() && this->size() != 1)
        {
            string += getZeroStringForBase();
            continue;
        }

        while (numberOfZeros > 0 && (i != this->size() - 1))
        {
            string += "0";
            --numberOfZeros;
        }
        string += std::to_string(this->vector_[i]);
    }

    return string;
}

BigInt BigInt::getBigger(const BigInt &first, const BigInt &second)
{
    BigInt firstTemp(first);
    BigInt secondTemp(second);
    return (firstTemp >= secondTemp) ? first : second;
}

BigInt BigInt::getLower(const BigInt &first, const BigInt &second)
{
    BigInt firstTemp(first);
    BigInt secondTemp(second);
    return (firstTemp < secondTemp) ? first : second;
}

BigInt operator+(const BigInt& first, const BigInt& second)
{
    BigInt tempValue(first);
    tempValue += second;
    return tempValue;
}

BigInt operator-(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue -= second;
    return tempValue;
}

BigInt operator*(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue *= second;
    return tempValue;
}

BigInt operator/(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue /= second;
    return tempValue;
}

BigInt operator%(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue %= second;
    return tempValue;
}

BigInt operator&(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue &= second;
    return tempValue;
}

BigInt operator^(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue ^= second;
    return tempValue;
}

BigInt operator|(const BigInt &first, const BigInt &second)
{
    BigInt tempValue(first);
    tempValue |= second;
    return tempValue;
}
