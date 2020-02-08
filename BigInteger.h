//
// Created by Jean-Christophe Chevalier on 03/02/2020.
//

#ifndef MODULAR_OPERATIONS_BIGINTEGER_H
#define MODULAR_OPERATIONS_BIGINTEGER_H

#include <string>
#include <vector>

using namespace std;

class BigInteger {

public:
    BigInteger();

    BigInteger(const BigInteger &integer);

    BigInteger(const int &size);

    explicit BigInteger(const vector<unsigned long int> &);

    BigInteger operator+(const BigInteger &bigInteger) const;

    BigInteger operator-(const BigInteger &bigInteger) const;

    BigInteger operator*(const BigInteger &bigInteger) const;

    BigInteger operator>>(const int &k) const;

    bool operator>(const BigInteger &bigInteger) const;

    bool operator<(const BigInteger &bigInteger) const;

    bool operator==(const BigInteger &bigInteger) const;

    vector<unsigned long int> getNumber() const;

    int size() const;

    void printNumber();

    void writeFile() const;

    BigInteger modularAddition(const BigInteger &number_b, const BigInteger &modulo) const;

    BigInteger modularSubstraction(const BigInteger &number_b, const BigInteger &modulo) const;

    BigInteger modularMultiplication(const BigInteger &number_b, const BigInteger &modulo, const BigInteger &v,
                                     const BigInteger &r) const;

    BigInteger modulo_2_pow(int power) const;

    int getPow() const;

private:
    vector<unsigned long int> number;
};

#endif //MODULAR_OPERATIONS_BIGINTEGER_H