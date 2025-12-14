//
// Created by tommy on 13/12/2025.
//

#include "DataStoreCSV.h"
#include <fstream>
#include <sstream>

const std::string DataStoreCSV::utentiFile = "utenti.csv";
const std::string DataStoreCSV::contiFile = "conti.csv";
const std::string DataStoreCSV::transazioniFile = "transazioni.csv";

void DataStoreCSV::salva(const Banca& banca) {
    // ===== UTENTI =====
    {
        std::ofstream out(utentiFile);
        out << "idUtente,password\n";
        for (const auto& [id, u] : banca.getUtenti()) {
            out << u.getId() << "," << "HIDDEN\n"; // password reale non esposta
        }
    }

    // ===== CONTI =====
    {
        std::ofstream out(contiFile);
        out << "numeroConto,saldo,idUtente\n";
        for (const auto& [num, c] : banca.getConti()) {
            out << c.getNumeroConto() << ","
                << c.getSaldo() << ","
                << c.getOwnerId() << "\n";
        }
    }

    // ===== TRANSAZIONI =====
    {
        std::ofstream out(transazioniFile);
        out << "id,contoUscita,contoIngresso,importo,data\n";
        for (const auto& [num, c] : banca.getConti()) {
            for (const auto& t : c.getTransazioni()) {
                out << t.getId() << ","
                    << t.getContoUscita() << ","
                    << t.getContoIngresso() << ","
                    << t.getSomma() << ","
                    << t.getData() << "\n";
            }
        }
    }
}

void DataStoreCSV::carica(Banca& banca) {
    // ===== UTENTI =====
    {
        std::ifstream in(utentiFile);
        std::string line;
        std::getline(in, line); // header
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string id, pw;
            std::getline(ss, id, ',');
            std::getline(ss, pw, ',');
            banca.registraUtente(id, pw);
        }
    }

    // ===== CONTI =====
    {
        std::ifstream in(contiFile);
        std::string line;
        std::getline(in, line);
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string num, saldo, owner;
            std::getline(ss, num, ',');
            std::getline(ss, saldo, ',');
            std::getline(ss, owner, ',');

            banca.creaContoDaFile(
                    std::stoi(num),
                    std::stoi(saldo),
                    owner
            );
        }
    }

    // ===== TRANSAZIONI =====
    {
        std::ifstream in(transazioniFile);
        std::string line;
        std::getline(in, line);
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string id, usc, ing, imp, data;
            std::getline(ss, id, ',');
            std::getline(ss, usc, ',');
            std::getline(ss, ing, ',');
            std::getline(ss, imp, ',');
            std::getline(ss, data, ',');

            Transazione t(
                    std::stoi(id),
                    std::stoi(usc),
                    std::stoi(ing),
                    std::stoi(imp),
                    data
            );
            banca.applicaTransazione(t);
        }
    }
}
