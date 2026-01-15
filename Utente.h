//
// Created by tommy on 21/11/2025.
//

#ifndef PROGETTOLABPROGRAMMAZIONE_UTENTE_H
#define PROGETTOLABPROGRAMMAZIONE_UTENTE_H
#include <string>
#include <vector>


class Utente {
private:
    std::string idUtente;
    std::string password;
    std::vector<int> listaConti;

public:
    Utente(const std::string& id, const std::string& pw);
    Utente() = default;

    const std::string& getId() const;
    bool verificaPassword(const std::string& pw) const;

    const std::vector<int>& getConti() const;
    void aggiungiConto(int numeroConto);
    void setPassword(const std::string& newPw);
    const std::string& getPassword() const;
    void setPasswordCaricata(const std::string& hash);
    void setId(const std::string& id);
};


#endif //PROGETTOLABPROGRAMMAZIONE_UTENTE_H
