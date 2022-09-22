#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum Consts : int
{
    BASE = 1000
};

class BigInt
{
private:
    std::vector<int> vector_;
    bool sign_;
public:
    BigInt();
    explicit BigInt(int value);
    BigInt(std::string string);
    BigInt(const BigInt &origin);
    ~BigInt();


    BigInt& operator=(const BigInt &other);
    BigInt operator~() const;
    BigInt& operator++();
    const BigInt operator++(int) const;
    BigInt& operator--();
    const BigInt operator--(int) const;

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
    friend std::ostream& operator<<(std::ostream &o, const BigInt &value);
};

BigInt operator+(const BigInt &first, const BigInt &second);
BigInt operator-(const BigInt &first, const BigInt &second);
BigInt operator*(const BigInt &first, const BigInt &second);
BigInt operator/(const BigInt &first, const BigInt &second);
BigInt operator^(const BigInt &first, const BigInt &second);
BigInt operator%(const BigInt &first, const BigInt &second);
BigInt operator&(const BigInt &first, const BigInt &second);
BigInt operator|(const BigInt &first, const BigInt &second);

#endif //BIGINT_BIGINT_H
