//
// Created by Jean-Christophe Chevalier on 03/02/2020.
//

#include "BigInteger.h"
#include <iostream>
#include <fstream>

BigInteger::BigInteger() = default;

BigInteger::BigInteger(const vector<unsigned long int> &number) {
    this->number = number;
}

BigInteger::BigInteger(const BigInteger &bigInteger) {
    this->number = bigInteger.getNumber();
}

vector<unsigned long int> BigInteger::getNumber() const {
    return number;
}

int BigInteger::size() const {
    return number.size();
}

BigInteger BigInteger::modularAddition(const BigInteger &number_b, const BigInteger &modulo) const {

    BigInteger output = *this;
    output = output + number_b;

    if (output > modulo) {
        output = output - modulo;
    }
    return output;
}

BigInteger BigInteger::modularSubstraction(const BigInteger &number_b, const BigInteger &modulo) const {

    BigInteger output = *this;

    if (output < number_b) {
        output = output + modulo;
    }

    output = output - number_b;

    return output;
}

BigInteger BigInteger::operator+(const BigInteger &bigInteger) const {

    vector<unsigned long int> vector_b = bigInteger.getNumber();
    vector<unsigned long int> output;
    unsigned long int a_value = 0;
    unsigned long int b_value = 0;
    unsigned long int intermediate_value = 0;
    unsigned long int overflow = 0;

    for (int i = this->size() - 1; i >= 0; i--) {
        a_value = number.at(i);
        b_value = vector_b.at(i);
        intermediate_value = a_value + b_value + overflow;
        overflow = intermediate_value >> 32;
        intermediate_value = intermediate_value - (overflow << 32);
        output.insert(output.begin(), intermediate_value);
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

bool BigInteger::operator>(const BigInteger &bigInteger) const {
    vector<unsigned long int> vector_b = bigInteger.getNumber();
    for (int i = 0; i < this->size(); i++) {
        if (this->number[i] > vector_b[i]) {
            return true;
        } else if (this->number[i] < vector_b[i]) {
            return false;
        }
    }
}

bool BigInteger::operator<(const BigInteger &bigInteger) const {
    vector<unsigned long int> vector_b = bigInteger.getNumber();
    for (int i = 0; i < this->size(); i++) {
        if (this->number[i] < vector_b[i]) {
            return true;
        } else if (this->number[i] > vector_b[i]) {
            return false;
        }
    }
}

void BigInteger::writeFile() const {
    string const file("../data.txt");
    ofstream flux(file.c_str(), ios::app);

    if (flux) {
        for (auto &i : this->number) {
            flux << i;
            if (i != this->number.at(this->number.size() - 1)) {
                flux << " ";
            }
        }
        flux << "\n";
    } else {
        cout << "Error: impossible to write in the file" << endl;
    }
}

void BigInteger::printNumber() {
    for (auto i = 0; i < this->number.size(); i++) {
        unsigned int val = this->number[i];
        int size = to_string(val).length();
        for (int j = 0; j < 10 - size; j++) {
            std::cout << " ";
        }
        std::cout << val << " ";
    }
    std::cout << "\n";
}