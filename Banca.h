//
// Created by tommy on 02/12/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_BANCA_H
#define PROGETTOLABPROGRAMMAZIONE_BANCA_H
#include <vector>
#include "Utente.h"
#include "ContoCorrente.h"
#include "Transazione.h"
#include <map>

class Banca {
private:
    std::map<std::string, Utente> utenti;
    std::map<int, ContoCorrente> conti;
public:
    Utente* login(const std::string& id, const std::string& pw);

    bool registraUtente(const std::string& id, const std::string& pw);

    ContoCorrente* creaConto(Utente& u, int saldoIniziale);

    ContoCorrente* trovaConto(int numero);
    void applicaTransazione(const Transazione& t);
    void creaContoDaFile(int numero, int saldo, const std::string& ownerId);
    const std::map<std::string, Utente>& getUtenti() const;
    const std::map<int, ContoCorrente>& getConti() const;

    void caricaUtenteDaFile(const std::string &id, const std::string &hash);
};


#endif //PROGETTOLABPROGRAMMAZIONE_BANCA_H
