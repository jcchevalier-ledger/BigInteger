//
// Created by Jean-Christophe Chevalier on 03/02/2020.
//

#include "BigInteger.h"
#include <iostream>

BigInteger::BigInteger(const vector<unsigned long int> &number) {
    this->number = number;
    cout << "New assigned number: ";
}

BigInteger::BigInteger() = default;

void BigInteger::printNumber() {
    for (auto &i : this->number) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
}

vector<unsigned long int> BigInteger::getNumber() const {
    return number;
}

int BigInteger::getSize() const {
    return number.size();
}