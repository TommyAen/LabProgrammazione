//
// Created by tommy on 19/04/2025.
//

#include "ContoCorrente.h"

ContoCorrente::ContoCorrente(int numero, const std::string& owner) : numeroConto(numero), saldo(0), ownerId(owner) {}

int ContoCorrente::getNumeroConto() const{ return numeroConto; }
int ContoCorrente::getSaldo() const{return saldo; }

const std::vector<Transazione>& ContoCorrente::getTransazioni() const {
    return transazioni;
}

void ContoCorrente::aggiungiTransazione(const Transazione &t) {
    transazioni.push_back(t);
}

void ContoCorrente::applicaTransazione(const Transazione &t) {
    if(t.getContoUscita()==numeroConto)
        saldo -= t.getSomma();

    if (t.getContoIngresso() == numeroConto)
        saldo += t.getSomma();

    transazioni.push_back(t);
}

const std::string &ContoCorrente::getOwnerId() const {
    return ownerId;
}

void ContoCorrente::setSaldo(int nuovoSaldo) {
    saldo = nuovoSaldo;
}
