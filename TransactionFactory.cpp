//
// Created by tommy on 11/12/2025.
//

#include "TransactionFactory.h"

unsigned long TransactionFactory::nextId = 1;

Transazione TransactionFactory::creaTransazione(int from, int to, int amount, const std::string &data) {
    return Transazione(nextId++, from, to, amount, data);
}