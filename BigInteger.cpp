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

BigInteger::BigInteger(const int &size) {
    this->number = vector<unsigned long int>(size);
    this->number.reserve(size);
}

vector<unsigned long int> BigInteger::getNumber() const {
    return number;
}

int BigInteger::size() const {
    return number.size();
}

BigInteger BigInteger::modularAddition(const BigInteger &number_b, const BigInteger &modulo) const {

    BigInteger this_copy = *this + number_b;
    BigInteger output;

    if (this_copy > modulo) {
        output = this_copy - modulo;
    } else {
        output = this_copy;
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
    vector<unsigned long int> this_copy = this->number;
    vector<unsigned long int> output;
    unsigned long int a_value = 0;
    unsigned long int b_value = 0;
    unsigned long int intermediate_value = 0;
    unsigned long int overflow = 0;

    if (this_copy.size() < bigInteger.size()) {
        this_copy.insert(this_copy.begin(), bigInteger.size() - this_copy.size(), 0);
    } else if (this_copy.size() > bigInteger.size()) {
        vector_b.insert(vector_b.begin(), this_copy.size() - bigInteger.size(), 0);
    }

    for (int i = this_copy.size() - 1; i >= 0; i--) {

        a_value = this_copy.at(i);
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

BigInteger BigInteger::operator*(const BigInteger &bigInteger) const {

    vector<unsigned long int> vector_b = bigInteger.getNumber();
    BigInteger array_intermediate_output[vector_b.size() * this->size()];
    BigInteger output = BigInteger(vector_b.size() + this->size());
    vector<unsigned long int> intermediate_result;

    unsigned long long int multiplication_result = 0;
    unsigned long int overflow = 0;
    int i = 0;
    int this_size = this->size() - 1;
    int b_size = vector_b.size() - 1;

    for (int this_index = this_size; this_index >= 0; this_index--) {

        for (int b_index = b_size; b_index >= 0; b_index--) {
            multiplication_result = vector_b[b_index] * this->number[this_index];
            overflow = multiplication_result >> 32;
            unsigned long int debug = multiplication_result - (overflow << 32);
            intermediate_result.insert(intermediate_result.begin(),
                                       debug);
            intermediate_result.insert(intermediate_result.begin(),
                                       (unsigned long int) overflow);

            intermediate_result.insert(
                    intermediate_result.end(),
                    this_size + b_size - (this_index + b_index),
                    (unsigned long int) 0
            );

            array_intermediate_output[i] = BigInteger(intermediate_result);

            intermediate_result.clear();
            i++;
        }
    }

    for (int intermediate_index = 0; intermediate_index < i; intermediate_index++) {
        output = output + array_intermediate_output[intermediate_index];
    }
    return output;
}

BigInteger BigInteger::operator>>(const int &k) const {

    vector<unsigned long int> this_copy = this->getNumber();
    unsigned long int rest = 0;
    unsigned long int value_to_add = 0;
    unsigned long int insert_value = 0;
    vector<unsigned long int> output;

    int suppressed_bytes = k / 32;
    int suppressed_bits = k % 32;

    for (int i = 0; i < suppressed_bytes; i++) {
        this_copy.pop_back();
    }

    rest = (this_copy[0] >> suppressed_bits);
    insert_value = (value_to_add + rest);
    output.insert(output.begin(), insert_value);

    for (int i = 1; i < this_copy.size(); i++) {
        value_to_add = this_copy[i - 1] << (32 - suppressed_bits) & 0xFFFFFFFF;
        rest = (this_copy[i] >> suppressed_bits);
        insert_value = (value_to_add + rest);
        output.insert(output.end(), insert_value);
    }

    if (output[0] == 0) {
        output.erase(output.begin());
    }
    return (BigInteger(output));
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
    return false;
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
    return false;
}

bool BigInteger::operator==(const BigInteger &bigInteger) const {
    vector<unsigned long int> vector_b = bigInteger.getNumber();
    for (int i = 0; i < this->size(); i++) {
        if (this->number[i] < vector_b[i]) {
            return false;
        } else if (this->number[i] > vector_b[i]) {
            return false;
        }
    }
    return true;
}

void BigInteger::writeFile() const {
    string const file("../data.txt");
    ofstream flux(file.c_str(), ios::app);

    if (flux) {
        for (auto &i : this->number) {
            flux << i << " ";
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

int BigInteger::getPow() const {

    BigInteger r_copy = *this;
    unsigned int byte = r_copy.size() - 1;
    unsigned int bit = 0;
    unsigned long int intermediate_value = r_copy.getNumber()[0];

    while (intermediate_value != 1) {
        intermediate_value = intermediate_value >> 1;
        bit += 1;
    }

    return ((byte * 32) + bit);
}

BigInteger BigInteger::modulo_2_pow(int power) const {
    int byte = power / 32;
    int bit = power % 32;
    vector<unsigned long int> modulo_array;
    vector<unsigned long int> output;

    for (int i = this->size() - 1; i > this->size() - 1 - byte; i--) {
        output.insert(output.begin(), number.at(i));
    }

    unsigned long int surplus = (number.at(this->size() - 1 - byte) >> (bit)) << (bit);
    output.insert(output.begin(), number.at(this->size() - 1 - byte) - surplus);
    return BigInteger(output);
}

BigInteger BigInteger::modularMultiplication(const BigInteger &number_b, const BigInteger &modulo, const BigInteger &v,
                                             const BigInteger &r) const {

    BigInteger this_copy = *this;
    BigInteger s = BigInteger();
    BigInteger t = BigInteger();
    BigInteger m = BigInteger();
    BigInteger u;

    int k = modulo.getPow();

    //Compute s = A * B

    s = this_copy * number_b;

    //Compute t = (s * v) mod r

    t = (s * v).modulo_2_pow(k);

    //Compute m = s + t * n

    m = s + t * modulo;

    //Compute u = m/r

    u = m >> k;

    while (u > modulo || u == modulo) {
        u = u - modulo;
    }

    return u;
}