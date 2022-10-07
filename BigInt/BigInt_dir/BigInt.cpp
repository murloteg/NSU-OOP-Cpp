#include "BigInt.h"

BigInt::BigInt()
{
    this->sign_ = false;
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

    int realSize = (length / 3) + 1 * (length % 3 != 0);
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
        return;
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
        if (this->size() == 1)
        {
            return;
        }

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

void BigInt::ConvertToBinaryString()
{
    this->binaryNotation = "";
    BigInt two(2);
    while (!IsEqualsZero(*this))
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

int BigInt::GetNumberOfZerosFromCell(int value) const
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

void BigInt::Swap(BigInt& first, BigInt& second)
{
    BigInt tempValue(first);
    first = second;
    second = tempValue;
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
        if (IsEqualsZero(*this))
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

    DeleteZeros();
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
        BigInt bigger(GetBigger(*this, other));
        BigInt lower(GetLower(*this, other));
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
    if (IsEqualsZero(*this))
    {
        BigInt tempValue(other);
        if (IsEqualsZero(tempValue))
        {
            tempValue.sign_ = true;
        }

        *this = -tempValue;
        return *this;
    }

    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_ || this->sign_ && other.sign_)
    {
        BigInt bigger(GetBigger(*this, other));
        BigInt lower(GetLower(*this, other));
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
    DeleteZeros();
    return *this;
}

BigInt &BigInt::DivideBy2(BigInt& value)
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

int BigInt::GetRemainderBy2(BigInt& value)
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

    if (this->sign_ != second.sign_)
    {
        this->sign_ = result.sign_ = false;
        result.sign_ = true;
    }

    first.sign_ = second.sign_ = false;
    if (first.size() < second.size())
    {
        Swap(first, second);
    }

    while (!IsEqualsZero(second))
    {
        if (GetRemainderBy2(second) == 0)
        {
            first = first + first;
            second = DivideBy2(second);
        }

        else
        {
            second -= 1;
            result += first;
        }
    }

    *this = result;
    return *this;
}

BigInt& BigInt::operator/=(const BigInt &other)
{
    BigInt result(0);
    if (this->sign_ && !other.sign_ || !this->sign_ && other.sign_)
    {
        this->sign_ = result.sign_ = false;
        result.sign_ = true;
    }

    BigInt currentValue(0);
    BigInt first(*this);
    BigInt second(other);

    for (int i = first.size() - 1; i >= 0; --i)
    {
        currentValue *= BASE;
        currentValue.vector_[0] = first.vector_[i];

        int currentDivider = 0;
        int left = 0;
        int right = BASE;
        BigInt middle_temp(0);
        BigInt cur(0);
        while (left <= right)
        {
            int middle = (left + right) / 2;
            middle_temp = middle;
            cur = middle_temp * second;
            if (cur <= currentValue)
            {
                currentDivider = middle;
                left = middle + 1;
            }

            else
            {
                right = middle - 1;
            }
        }

        result *= BASE;
        result += currentDivider;
        BigInt currDivObj(currentDivider);
        currentValue = currentValue - second * currDivObj;
    }

    *this = result;
    DeleteZeros();
    return *this;
}

BigInt& BigInt::operator%=(const BigInt &other)
{
    BigInt tempValue(*this);
    tempValue /= other;
    *this = (*this - tempValue * other);
    return *this;
}

void BigInt::AddMoreZeros(std::string &string, int count)
{
    std::reverse(string.begin(), string.end());
    for (int i = 0; i < count; ++i)
    {
        string += "0";
    }
    std::reverse(string.begin(), string.end());
}

BigInt BigInt::ConvertFromBinaryNotation(std::string &string)
{
    int realSize = static_cast<int> (string.length() / 8);
    BigInt result(0);
    result.vector_.resize(realSize);
    BigInt tempValue(1);
    int indexInString = 0;
    int remainderOfStringLength = static_cast<int> (string.length() % 8);
    if (remainderOfStringLength != 0)
    {
        for (int j = 0; j < remainderOfStringLength; ++j)
        {
            result += (string[(realSize * 8 + remainderOfStringLength - 1) - j] == '0') ? static_cast<BigInt> (0) : tempValue;
            tempValue *= 2;
        }
    }

    for (int i = 0; i < realSize; ++i)
    {
        indexInString = (realSize == 1) ? 7 : 8 * (realSize - i) - 1; // TODO: remove magic constants
        for (int j = 0; j < 8; ++j)
        {
            result += (string[indexInString - j] == '0') ? static_cast<BigInt> (0) : tempValue;
            tempValue *= 2;
        }
    }

    return result;
}

BigInt BigInt::BitwiseXOR(std::string& first, std::string& second)
{
    int maxLength = static_cast<int> (std::max(first.length(), second.length()));
    if (first.length() != maxLength || first.length() < 8)
    {
        AddMoreZeros(first, static_cast<int> (maxLength - first.length()));
    }

    else if (second.length() != maxLength || second.length() < 8)
    {
        AddMoreZeros(second, static_cast<int> (maxLength - second.length()));
    }

    if (first.length() <= 8 && second.length() <= 8)
    {
        AddMoreZeros(first, static_cast<int> (8 - first.length()));
        AddMoreZeros(second, static_cast<int> (8 - second.length()));
        maxLength = 8; // TODO: remove magic consts.
    }

    std::string result;
    for (int i = 0; i < maxLength; ++i)
    {
        if (first[i] == second[i])
        {
            result += '0';
        }

        else
        {
            result += '1';
        }
    }

    BigInt tempValue = ConvertFromBinaryNotation(result);
    tempValue.DeleteZeros();
    return tempValue;
}

BigInt& BigInt::operator^=(const BigInt &other)
{
    this->ConvertToBinaryString();
    BigInt second(other);
    second.ConvertToBinaryString();
    *this = BitwiseXOR(this->binaryNotation, second.binaryNotation);
    return *this;
}

BigInt BigInt::BitwiseAND(std::string& first, std::string& second)
{
    std::string result;
    int maxLength = static_cast<int> (std::max(first.length(), second.length()));
    if (first.length() != maxLength || first.length() < 8)
    {
        AddMoreZeros(first, static_cast<int> (maxLength - first.length()));
    }

    else if (second.length() != maxLength || second.length() < 8)
    {
        AddMoreZeros(second, static_cast<int> (maxLength - second.length()));
    }

    if (first.length() <= 8 && second.length() <= 8)
    {
        AddMoreZeros(first, static_cast<int> (8 - first.length()));
        AddMoreZeros(second, static_cast<int> (8 - second.length()));
        maxLength = 8; // TODO: remove magic consts.
    }

    for (int i = 0; i < maxLength; ++i)
    {
        if (first[i] == '1' && second[i] == '1')
        {
            result += '1';
        }

        else
        {
            result += '0';
        }
    }

    BigInt tempValue = ConvertFromBinaryNotation(result);
    tempValue.DeleteZeros();
    return tempValue;
}

BigInt &BigInt::operator&=(const BigInt &other)
{
    this->ConvertToBinaryString();
    BigInt second(other);
    second.ConvertToBinaryString();
    *this = BitwiseAND(this->binaryNotation, second.binaryNotation);
    return *this;
}

BigInt &BigInt::operator|=(const BigInt &other)
{
    return *this; // TODO: add assignment "or" operator.
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
    for (int i = static_cast<int> (this->size() - 1); i >= 0; --i)
    {
        result = result * BASE + this->vector_[i];
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
        int numberOfZeros = GetNumberOfZerosFromCell(this->vector_[i]);
        if (numberOfZeros == 3 && this->size() != 1)
        {
            string += "000";
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

BigInt BigInt::GetBigger(const BigInt &first, const BigInt &second)
{
    BigInt firstTemp(first);
    BigInt secondTemp(second);
    return (firstTemp >= secondTemp) ? first : second;
}

BigInt BigInt::GetLower(const BigInt &first, const BigInt &second)
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
    return BigInt();
}
