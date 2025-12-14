//
// Created by tommy on 02/12/2025.
//

#include "Banca.h"

Utente* Banca::login(const std::string& id, const std::string& pw) {
    for (auto& [id, u] : utenti) {
        if (u.getId() == id && u.verificaPassword(pw))
            return &u;
    }
    return nullptr;
}

bool Banca::registraUtente(const std::string& id, const std::string& pw) {
    if (utenti.contains(id))
        return false;

    utenti.emplace(id, Utente(id, pw));
    return true;
}


ContoCorrente* Banca::creaConto(Utente& u) {
    int nuovoNumero = conti.size() + 1;
    conti.emplace(nuovoNumero, ContoCorrente(nuovoNumero, u.getId()));
    u.aggiungiConto(nuovoNumero);
    auto it = conti.find(nuovoNumero);
    return &it->second;
}

ContoCorrente* Banca::trovaConto(int numero) {
    auto it = conti.find(numero);
    if (it != conti.end())
        return &it->second;

    return nullptr;
}


void Banca::applicaTransazione(const Transazione& t) {
    auto* uscita = trovaConto(t.getContoUscita());
    auto* ingresso = trovaConto(t.getContoIngresso());

    if (uscita) uscita->applicaTransazione(t);
    if (ingresso) ingresso->applicaTransazione(t);
}

const std::map<std::string, Utente>& Banca::getUtenti() const {
    return utenti;
}

const std::map<int, ContoCorrente>& Banca::getConti() const {
    return conti;
}

void Banca::creaContoDaFile(int numero, int saldo, const std::string& ownerId) {

    // Inserisce il conto solo se non esiste già
    conti.emplace(
            numero,
            ContoCorrente(numero, ownerId)
    );

    // Imposta il saldo
    conti.find(numero)->second.setSaldo(saldo);

    // Collega il conto all'utente (se esiste)
    auto itUtente = utenti.find(ownerId);
    if (itUtente != utenti.end()) {
        itUtente->second.aggiungiConto(numero);
    }
}
