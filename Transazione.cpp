//
// Created by tommy on 02/12/2025.
//

#include "Transazione.h"
#include <sstream>

Transazione::Transazione(unsigned long id, int uscita, int ingresso, int amount, const std::string &dt) :
    idTransazione(id),
    contoUscita(uscita),
    contoIngresso(ingresso),
    sommaCentesimi(amount),
    data(dt){}

Transazione::Transazione() {}

unsigned long Transazione::getId() const{ return idTransazione; }
int Transazione::getContoUscita() const { return contoUscita; }
int Transazione::getContoIngresso() const { return contoIngresso; }
int Transazione::getSomma() const { return sommaCentesimi; }
const std::string& Transazione::getData() const { return data; }

std::string Transazione::toCSV() const {
    std::ostringstream oss;
    oss  << idTransazione << ","
         << contoUscita << ","
         << contoIngresso << ","
         << sommaCentesimi << ","
         << data;
    return oss.str();
}

Transazione Transazione::fromCSV(const std::string& line) {
    std::stringstream ss(line);
    std::string token;

    unsigned long id;
    int uscita, ingresso, amount;
    std::string dt;

    std::getline(ss, token, ','); id = std::stoul(token);
    std::getline(ss, token, ','); uscita = std::stoi(token);
    std::getline(ss, token, ','); ingresso = std::stoi(token);
    std::getline(ss, token, ','); amount = std::stoi(token);
    std::getline(ss, dt);

    return Transazione(id, uscita, ingresso, amount, dt);
}