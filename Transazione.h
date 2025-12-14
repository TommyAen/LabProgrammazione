//
// Created by tommy on 02/12/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_TRANSAZIONE_H
#define PROGETTOLABPROGRAMMAZIONE_TRANSAZIONE_H

#include <string>

class Transazione {
private:
    unsigned long idTransazione;
    int contoUscita;
    int contoIngresso;
    int sommaCentesimi;
    std::string data;

public:
    Transazione();
    Transazione(unsigned long id, int uscita, int ingresso, int amount, const std::string& dt);

    unsigned long getId() const;
    int getContoUscita() const;
    int getContoIngresso() const;
    int getSomma() const;
    const std::string& getData() const;

    std::string toCSV() const;
    static Transazione fromCSV(const std::string& line);
};


#endif //PROGETTOLABPROGRAMMAZIONE_TRANSAZIONE_H
