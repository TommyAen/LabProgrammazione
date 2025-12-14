//
// Created by tommy on 13/12/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_DATASTORECSV_H
#define PROGETTOLABPROGRAMMAZIONE_DATASTORECSV_H
#include <string>
#include "Banca.h"

class DataStoreCSV {
public:
    static void salva(const Banca& banca);
    static void carica(Banca& banca);
private:
    static const std::string utentiFile;
    static const std::string contiFile;
    static const std::string transazioniFile;
};


#endif //PROGETTOLABPROGRAMMAZIONE_DATASTORECSV_H
