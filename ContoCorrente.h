//
// Created by tommy on 19/04/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_CONTOCORRENTE_H
#define PROGETTOLABPROGRAMMAZIONE_CONTOCORRENTE_H
#include <vector>
#include "Transazione.h"

class ContoCorrente {
private:
    int numeroConto;
    int saldo; //intero per maggiore precisione, il totale è salvato in centesimi
    std::string ownerId;
    std::vector<Transazione> transazioni;

public:
    ContoCorrente(int numero, const std::string& owner);

    int getNumeroConto() const;
    int getSaldo() const;
    void setSaldo(int nuovoSaldo);
    const std::vector<Transazione>& getTransazioni() const;
    const std::string& getOwnerId() const;

    void applicaTransazione(const Transazione& t);
    void aggiungiTransazione(const Transazione& t);
};


#endif //PROGETTOLABPROGRAMMAZIONE_CONTOCORRENTE_H
