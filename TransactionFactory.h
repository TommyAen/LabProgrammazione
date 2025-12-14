//
// Created by tommy on 11/12/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_TRANSACTIONFACTORY_H
#define PROGETTOLABPROGRAMMAZIONE_TRANSACTIONFACTORY_H
#include "Transazione.h"

class TransactionFactory {
private:
    static unsigned long nextId;
public:
    static Transazione creaTransazione(int from, int to, int amount, const std::string& data);
};


#endif //PROGETTOLABPROGRAMMAZIONE_TRANSACTIONFACTORY_H
