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

    explicit BigInteger(const vector<unsigned long int> &);

    vector<unsigned long int> getNumber() const;

    int size() const;

    void printNumber();

    BigInteger operator+(const BigInteger &bigInteger) const;

    BigInteger operator-(const BigInteger &bigInteger) const;

    bool operator>(const BigInteger &bigInteger) const;

    bool operator<(const BigInteger &bigInteger) const;

    void writeFile() const;

private:
    vector<unsigned long int> number;

    BigInteger modularAddition(const BigInteger &number_b, const BigInteger &modulo);
};


#endif //MODULAR_OPERATIONS_BIGINTEGER_H
