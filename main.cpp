#include <iostream>
#include <string>
#include <cmath>

#include "Banca.h"
#include "Utente.h"
#include "ContoCorrente.h"
#include "Transazione.h"
#include "TransactionFactory.h"
#include "DataStoreCSV.h"

static std::string read_line_trim() {
    std::string s;
    std::getline(std::cin, s);
    // trim simple (left + right)
    const char* ws = " \t\n\r";
    size_t start = s.find_first_not_of(ws);
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

static void wait_enter() {
    std::cout << "Premi invio per continuare...";
    std::string tmp;
    std::getline(std::cin, tmp);
}

//Insieme dei menu
void menu_login(Banca& banca);
Utente* esegui_login(Banca& banca);
void esegui_registrazione(Banca& banca);
void menu_home(Banca& banca, Utente* user);
void visualizza_conti(Banca& banca, Utente* user);
void modifica_profilo(Utente* user);
void fai_transazione(Banca& banca, Utente* user);

int main() {
    Banca banca;

    DataStoreCSV::carica(banca);

    std::cout << "++++ Benvenuto ++++";
    menu_login(banca);
    DataStoreCSV::salva(banca);
    return 0;
}

void menu_login(Banca& banca){
    while(true){
        std::cout << "\n++++ LOGIN ++++\n";
        std::cout << "1. Accedi\n";
        std::cout << "2. Registrati\n";
        std::cout << "3. Esci (termina applicazione)\n";
        std::cout << "Scelta: ";
        std::string choice = read_line_trim();

        if (choice == "1") {
            Utente* u = esegui_login(banca);
            if (u) {
                menu_home(banca, u);
                // dopo ritorno alla schermata di login
            }
        } else if (choice == "2") {
            esegui_registrazione(banca);
        } else if (choice == "3") {
            std::cout << "Uscita. Arrivederci!\n";
            return;
        } else {
            std::cout << "Scelta non valida, riprova.\n";
        }
    }
}

Utente* esegui_login(Banca& banca){
    std::cout << "\n++++ Login ++++\n";
    std::cout << "ID: ";
    std::string id = read_line_trim();
    std::cout << "Password: ";
    std::string pw = read_line_trim();

    Utente* u = banca.login(id, pw);
    if(!u){
        std::cout << "Credenziali errate.\n";
        return nullptr;
    }
    std::cout << "Login avvenuto con successo.\n";
    return u;
}

void esegui_registrazione(Banca& banca) {
    std::cout << "\n++++ Registrazione nuovo utente ++++\n";

    std::cout << "Scegli ID: ";
    std::string id = read_line_trim();

    std::cout << "Scegli Password: ";
    std::string pw = read_line_trim();

    bool ok = banca.registraUtente(id, pw);
    if (!ok) {
        std::cout << "ID già esistente. Registrazione annullata\n";
        wait_enter();
        return;
    }

    // Login automatico dopo registrazione
    Utente* u = banca.login(id, pw);
    if (!u) {
        std::cout << "Errore interno nella creazione utente.\n";
        wait_enter();
        return;
    }

    // Richiesta saldo iniziale
    std::cout << "Saldo iniziale (EUR, es: 100.50): ";
    std::string saldoStr = read_line_trim();

    double saldoDouble = 0.0;
    try { saldoDouble = std::stod(saldoStr); }
    catch (...) { saldoDouble = -1.0; }

    if (saldoDouble < 0.0) {
        std::cout << "Saldo non valido. Registrazione annullata.\n";
        wait_enter();
        return;
    }

    int saldoCents = static_cast<int>(std::llround(saldoDouble * 100.0));

    banca.creaConto(*u, saldoCents);

    std::cout << "Utente creato con conto iniziale da "
              << (saldoCents / 100) << " EUR "
              << (std::abs(saldoCents) % 100) << "c\n";

    wait_enter();
}


void menu_home(Banca& banca, Utente* user) {
    while (true) {
        std::cout << "\n++++ HOME (" << user->getId() << ") ++++\n";
        std::cout << "1. Visualizza conti\n";
        std::cout << "2. Crea nuovo conto corrente\n";
        std::cout << "3. Modifica profilo\n";
        std::cout << "4. Fai transazione\n";
        std::cout << "5. Logout (torna al login)\n";
        std::cout << "Scelta: ";
        std::string choice = read_line_trim();

        if (choice == "1") {
            visualizza_conti(banca, user);
        }
        else if (choice == "2") {
            std::cout << "Saldo iniziale (EUR, es: 100.50): ";
            std::string saldoStr = read_line_trim();

            double saldoDouble = 0.0;
            try { saldoDouble = std::stod(saldoStr); } catch (...) { saldoDouble = 0.0; }

            if (saldoDouble < 0.0) {
                std::cout << "Saldo non valido.\n";
                wait_enter();
                return;
            }

            int saldoCents = static_cast<int>(std::llround(saldoDouble * 100.0));

            ContoCorrente* c = banca.creaConto(*user, saldoCents);

            std::cout << "Conto creato con saldo iniziale di "
                      << (saldoCents / 100) << " EUR "
                      << (std::abs(saldoCents) % 100) << "c\n";

            wait_enter();
        }
        else if (choice == "3") {
            modifica_profilo(user);
        }
        else if (choice == "4") {
            fai_transazione(banca, user);
        }
        else if (choice == "5") {
            std::cout << "Logout effettuato.\n";
            return;
        }
        else {
            std::cout << "Scelta non valida.\n";
        }

    }
}

void visualizza_conti(Banca& banca, Utente* user) {
    std::cout << "\n--- I tuoi conti ---\n";
    const auto& contiList = user->getConti();
    if (contiList.empty()) {
        std::cout << "Non hai conti.\n";
        wait_enter();
        return;
    }
    for (int numero : contiList) {
        ContoCorrente* c = banca.trovaConto(numero);
        if (!c) continue;
        std::cout << "Conto #" << c->getNumeroConto()
                  << " - Saldo: " << (c->getSaldo() / 100) << " EUR e " << (std::abs(c->getSaldo()) % 100) << " cent\n";
        const auto& txs = c->getTransazioni();
        if (txs.empty()) {
            std::cout << "  (Nessuna transazione)\n";
        } else {
            std::cout << "  Transazioni:\n";
            for (const auto& t : txs) {
                std::cout << "    ID:" << t.getId()
                          << " from:" << t.getContoUscita()
                          << " to:" << t.getContoIngresso()
                          << " amount:" << (t.getSomma() / 100) << "eur " << (std::abs(t.getSomma()) % 100) << "c"
                          << " date:" << t.getData() << "\n";
            }
        }
    }
    wait_enter();
}

void modifica_profilo(Utente* user) {
    while (true) {
        std::cout << "\n++++ Profilo (" << user->getId() << ") ++++\n";
        std::cout << "1. Cambia password\n";
        std::cout << "2. Torna alla Home\n";
        std::cout << "Scelta: ";
        std::string choice = read_line_trim();
        if (choice == "1") {
            std::cout << "Inserisci password corrente: ";
            std::string cur = read_line_trim();
            if (!user->verificaPassword(cur)) {
                std::cout << "Password corrente errata.\n";
                continue;
            }
            std::cout << "Inserisci nuova password: ";
            std::string npw = read_line_trim();
            user->setPassword(npw);
            std::cout << "Password aggiornata.\n";
        } else if (choice == "2") {
            return;
        } else {
            std::cout << "Scelta non valida.\n";
        }
    }
}

void fai_transazione(Banca& banca, Utente* user) {
    std::cout << "\n++++ Nuova transazione ++++\n";
    const auto& contiList = user->getConti();
    if (contiList.empty()) {
        std::cout << "Non hai conti su cui operare.\n";
        wait_enter();
        return;
    }

    std::cout << "Scegli il conto di uscita (numero):\n";
    for (int numero : contiList) {
        ContoCorrente* c = banca.trovaConto(numero);
        if (!c) continue;
        std::cout << "  - " << c->getNumeroConto() << " (saldo: " << (c->getSaldo()/100) << " EUR "
                  << (std::abs(c->getSaldo()) % 100) << "c)\n";
    }
    std::cout << "Numero conto uscita: ";
    std::string uscitaStr = read_line_trim();
    int uscitaNum = 0;
    try { uscitaNum = std::stoi(uscitaStr); } catch(...) { uscitaNum = 0; }

    ContoCorrente* uscita = banca.trovaConto(uscitaNum);
    if (!uscita) {
        std::cout << "Conto di uscita non trovato.\n";
        wait_enter();
        return;
    }

    std::cout << "Numero conto destinatario (inserire numero conto): ";
    std::string destStr = read_line_trim();
    int destNum = 0;
    try { destNum = std::stoi(destStr); } catch(...) { destNum = 0; }
    ContoCorrente* dest = banca.trovaConto(destNum);
    if (!dest) {
        std::cout << "Conto destinatario non trovato.\n";
        wait_enter();
        return;
    }

    std::cout << "Importo in formato EUR (es: 12.50): ";
    std::string impStr = read_line_trim();
    double imp = 0.0;
    try { imp = std::stod(impStr); } catch(...) { imp = 0.0; }
    if (imp <= 0.0) {
        std::cout << "Importo non valido.\n";
        wait_enter();
        return;
    }
    // converto in centesimi (int)
    int cents = static_cast<int>(std::llround(imp * 100.0));

    // controllo saldo
    if (uscita->getSaldo() < cents) {
        std::cout << "Saldo insufficiente sul conto di uscita.\n";
        wait_enter();
        return;
    }

    std::cout << "Data transazione (es: 2025-11-01): ";
    std::string data = read_line_trim();
    if (data.empty()) data = "n/a";

    // crea transazione
    Transazione t = TransactionFactory::creaTransazione(uscitaNum, destNum, cents, data);
    banca.applicaTransazione(t);

    std::cout << "Transazione eseguita: ID " << t.getId()
              << " - " << (t.getSomma()/100) << " EUR " << (std::abs(t.getSomma())%100) << "c\n";
    wait_enter();
}