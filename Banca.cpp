//
// Created by tommy on 02/12/2025.
//

#include "Banca.h"

Utente* Banca::login(const std::string& id, const std::string& pw) {
    auto it = utenti.find(id);
    if(it != utenti.end() && it->second.verificaPassword(pw)){
        return &(it->second);
    }
    return nullptr;
}

bool Banca::registraUtente(const std::string& id, const std::string& pw) {
    if (utenti.contains(id))
        return false;

    utenti.emplace(id, Utente(id, pw));
    return true;
}


ContoCorrente* Banca::creaConto(Utente& u, int saldoIniziale) {
    int nuovoNumero = conti.size() + 1;

    ContoCorrente conto(nuovoNumero, u.getId());
    conto.setSaldo(saldoIniziale);

    conti.emplace(nuovoNumero, conto);
    u.aggiungiConto(nuovoNumero);

    return &conti.find(nuovoNumero)->second;
}

void Banca::caricaUtenteDaFile(const std::string& id, const std::string& hash) {
    Utente u;
    u.setId(id);
    u.setPasswordCaricata(hash);
    utenti[id] = u;
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
