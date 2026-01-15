//
// Created by tommy on 21/11/2025.
//

#include "Utente.h"

static std::string hashStabile(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return std::to_string(hash);
}
//Inizialmente avevo usato std::hash, ma in quanto non deterministico se usato tra riavvii diversi ho dovuto implementare un hash deterministico

Utente::Utente(const std::string &id, const std::string &pw) : idUtente(id){
    this->password = hashStabile(pw);
}

const std::string& Utente::getId() const {return idUtente; }

bool Utente::verificaPassword(const std::string& pw) const{
    return this->password == hashStabile(pw);
}

const std::vector<int>& Utente::getConti() const{
    return listaConti;
}

void Utente::aggiungiConto(int numeroConto){
    listaConti.push_back(numeroConto);
}

void Utente::setPassword(const std::string &newPw) {
    this->password = hashStabile(newPw);
}

const std::string &Utente::getPassword() const {
    return password;
}
void Utente::setPasswordCaricata(const std::string& hash) {
    this->password = hash;
}

void Utente::setId(const std::string &id) {
    this->idUtente = id;
}
