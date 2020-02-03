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

    void printNumber();

private:
    vector<unsigned long int> number;

};


#endif //MODULAR_OPERATIONS_BIGINTEGER_H
