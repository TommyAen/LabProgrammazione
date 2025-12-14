//
// Created by tommy on 21/11/2025.
//

#include "Utente.h"

Utente::Utente(const std::string &id, const std::string &pw) : idUtente(id), password(pw){}

const std::string& Utente::getId() const {return idUtente; }

bool Utente::verificaPassword(const std::string& pw) const{
    return pw == password;
}

const std::vector<int>& Utente::getConti() const{
    return listaConti;
}

void Utente::aggiungiConto(int numeroConto){
    listaConti.push_back(numeroConto);
}

void Utente::setPassword(const std::string &newPw) {
    password = newPw;
}
