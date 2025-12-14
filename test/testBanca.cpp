//
// Created by tommy on 14/12/2025.
//

#include <gtest/gtest.h>
#include "../Banca.h"

#include <gtest/gtest.h>
#include "../Banca.h"
#include "../Transazione.h"

TEST(BancaTest, ApplicaTransazione) {
    Banca b;
    b.registraUtente("luca", "pw");
    Utente* u = b.login("luca", "pw");
    ContoCorrente* c = b.creaConto(*u, 1000);

    // Transazione verso lo stesso conto per deposito
    Transazione t(1, 0, c->getNumeroConto(), 500, "2025-12-14");
    b.applicaTransazione(t);

    EXPECT_EQ(c->getSaldo(), 1500);
    EXPECT_EQ(c->getTransazioni().size(), 1);

    // Transazione uscente
    Transazione t2(2, c->getNumeroConto(), 0, 200, "2025-12-14");
    b.applicaTransazione(t2);

    EXPECT_EQ(c->getSaldo(), 1300);
    EXPECT_EQ(c->getTransazioni().size(), 2);
}
