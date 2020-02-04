//
// Created by Jean-Christophe Chevalier on 03/02/2020.
//

#include "BigInteger.h"
#include <iostream>

BigInteger::BigInteger(const vector<unsigned long int> &number) {
    this->number = number;
}

BigInteger::BigInteger() = default;

void BigInteger::printNumber() {
    cout << "New assigned number: ";
    for (auto i = 0; i < this->number.size(); i++) {
        unsigned int number = this->number.at(i) * (1 << i * 31);
        int size = to_string(number).length();
        for (int j = 0; j < 10 - size; j++) {
            std::cout << "0";
        }
        std::cout << number << "";
    }
    std::cout << "\n";
}

BigInteger BigInteger::operator+(const BigInteger &bigInteger) {

    vector<unsigned long int> vector_b = bigInteger.getNumber();
    vector<unsigned long int> output;
    unsigned long int intermediate_value;
    unsigned long int overflow = 0;

    output.reserve(8);
    for (int i = this->size() - 1; i >= 0; --i) {
        intermediate_value = vector_b.at(i) + number.at(i) + overflow;
        overflow = intermediate_value >> 32;
        output.insert(output.begin(), intermediate_value - (overflow << 32));
    }
    if (overflow != 0) {
        output.insert(output.begin(), overflow);
    }
    return BigInteger(output);
}

BigInteger BigInteger::operator-(const BigInteger &bigInteger) const {

    vector<unsigned long int> vector_b = bigInteger.getNumber();
    vector<unsigned long int> output;
    unsigned long int a_value = 0;
    unsigned long int b_value = 0;
    unsigned long int intermediate_value = 0;
    unsigned long int overflow = 0;

    output.reserve(8);
    for (int i = this->size() - 1; i >= 0; --i) {
        if (overflow != 0) {
            b_value = vector_b.at(i) + 1;
        } else {
            b_value = vector_b.at(i);
        }
        a_value = number.at(i);
        if (a_value < b_value) {
            overflow = (unsigned long int) 1 << 32;
        } else {
            overflow = 0;
        }

        intermediate_value = a_value + overflow - b_value;
        output.insert(output.begin(), intermediate_value);
    }
    return BigInteger(output);
}

vector<unsigned long int> BigInteger::getNumber() const {
    return number;
}

int BigInteger::size() const {
    return number.size();
}