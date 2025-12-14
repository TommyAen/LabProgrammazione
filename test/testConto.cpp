//
// Created by tommy on 14/12/2025.
//

#include <gtest/gtest.h>
#include "../ContoCorrente.h"
#include "../Transazione.h"

TEST(ContoCorrenteTest, CostruttoreEGetter) {
    ContoCorrente c(101, "tommy");
    EXPECT_EQ(c.getNumeroConto(), 101);
    EXPECT_EQ(c.getOwnerId(), "tommy");
    EXPECT_EQ(c.getSaldo(), 0);
    EXPECT_TRUE(c.getTransazioni().empty());
}

TEST(ContoCorrenteTest, ModificaSaldo) {
    ContoCorrente c(102, "pippo");
    c.setSaldo(5000);
    EXPECT_EQ(c.getSaldo(), 5000);
}

TEST(ContoCorrenteTest, AggiungiTransazioni) {
    ContoCorrente c(103, "luca");
    Transazione t1(1, 0, 103, 1000, "2025-12-14");
    Transazione t2(2, 103, 0, 500, "2025-12-14");

    c.aggiungiTransazione(t1);
    c.aggiungiTransazione(t2);

    EXPECT_EQ(c.getTransazioni().size(), 2);

    EXPECT_EQ(c.getTransazioni()[0].getId(), 1);
    EXPECT_EQ(c.getTransazioni()[0].getContoIngresso(), 103);
    EXPECT_EQ(c.getTransazioni()[0].getSomma(), 1000);

    EXPECT_EQ(c.getTransazioni()[1].getId(), 2);
    EXPECT_EQ(c.getTransazioni()[1].getContoUscita(), 103);
    EXPECT_EQ(c.getTransazioni()[1].getSomma(), 500);
}
