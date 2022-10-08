#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum Consts : int {
    BASE = 1000,
    MAX_BIT_INDEX = 7,
    BIT_LENGTH = 8
};

class BigInt {
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
private:
    std::vector<int> vector_;
    bool sign_;
    std::string binaryNotation;
    void deleteZeros();
    bool isEqualsZero(const BigInt& object);
    bool checkSign();
    static int getLengthOfBase();
    BigInt getBigger(const BigInt& first, const BigInt& second);
    BigInt getLower(const BigInt& first, const BigInt& second);
    static int getNumberOfZerosFromCell(int value);
    BigInt& divideBy2(BigInt& value);
    static int getRemainderBy2(BigInt& value);
    static void swap(BigInt& first, BigInt& second);
    void convertToBinaryString();
    static BigInt convertFromBinaryNotation(std::string &string);
    static BigInt bitwiseXOR(std::string& first, std::string& second);
    static BigInt bitwiseAND(std::string& first, std::string& second);
    static BigInt bitwiseOR(std::string& first, std::string& second);
    static int prepareStringsAndGetMaxLength(std::string& first, std::string& second);
    static void addMoreZeros(std::string& string, int count);
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
