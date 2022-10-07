#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum Consts : int
{
    BASE = 1000,
    MAX_BIT_INDEX = 7,
    BIT_LENGTH = 8
};

class BigInt
{
private:
    std::vector<int> vector_;
    bool sign_;
    std::string binaryNotation;
    void DeleteZeros();
    bool IsEqualsZero(const BigInt& object);
    BigInt GetBigger(const BigInt& first, const BigInt& second);
    BigInt GetLower(const BigInt& first, const BigInt& second);
    void ConvertToBinaryString();
    static BigInt ConvertFromBinaryNotation(std::string &string);
    int GetNumberOfZerosFromCell(int value) const;
    BigInt& DivideBy2(BigInt& value);
    int GetRemainderBy2(BigInt& value);
    void Swap(BigInt& first, BigInt& second);
    static BigInt BitwiseXOR(std::string& first, std::string& second);
    static BigInt BitwiseAND(std::string& first, std::string& second);
    static BigInt BitwiseOR(std::string& first, std::string& second);
    static void AddMoreZeros(std::string& string, int count);
    bool CheckSign();
public:
    BigInt();
    BigInt(int value);
    BigInt(std::string string);
    BigInt(const BigInt &origin);
    ~BigInt();

    BigInt& operator=(const BigInt &other);
    BigInt operator~() const;
    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt &other);
    BigInt& operator-=(const BigInt &other);
    BigInt& operator*=(const BigInt &other);
    BigInt& operator/=(const BigInt &other);
    BigInt& operator^=(const BigInt &other);
    BigInt& operator%=(const BigInt &other);
    BigInt& operator&=(const BigInt &other);
    BigInt& operator|=(const BigInt &other);

    BigInt operator+() const;
    BigInt operator-() const;

    bool operator==(const BigInt &other);
    bool operator!=(const BigInt &other);
    bool operator<(const BigInt &other);
    bool operator>(const BigInt &other);
    bool operator<=(const BigInt &other);
    bool operator>=(const BigInt &other);

    operator int() const;
    operator std::string() const;

    size_t size() const;
};

BigInt operator+(const BigInt &first, const BigInt &second);
BigInt operator-(const BigInt &first, const BigInt &second);
BigInt operator*(const BigInt &first, const BigInt &second);
BigInt operator/(const BigInt &first, const BigInt &second);
BigInt operator^(const BigInt &first, const BigInt &second);
BigInt operator%(const BigInt &first, const BigInt &second);
BigInt operator&(const BigInt &first, const BigInt &second);
BigInt operator|(const BigInt &first, const BigInt &second);

std::ostream& operator<<(std::ostream &output, const BigInt &value);

#endif //BIGINT_BIGINT_H
