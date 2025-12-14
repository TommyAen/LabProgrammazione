//
// Created by tommy on 14/12/2025.
//

#include <gtest/gtest.h>
#include "../Utente.h"

TEST(UtenteTest, CostruttoreEGetter) {
    Utente u("tommy", "1234");
    EXPECT_EQ(u.getId(), "tommy");
    EXPECT_TRUE(u.verificaPassword("1234"));
    EXPECT_FALSE(u.verificaPassword("wrong"));
}

TEST(UtenteTest, GestioneConti) {
    Utente u("pippo", "abcd");
    EXPECT_TRUE(u.getConti().empty());

    u.aggiungiConto(1001);
    u.aggiungiConto(1002);

    std::vector<int> conti = u.getConti();
    EXPECT_EQ(conti.size(), 2);
    EXPECT_EQ(conti[0], 1001);
    EXPECT_EQ(conti[1], 1002);
}

TEST(UtenteTest, CambiaPassword) {
    Utente u("luca", "pass");
    u.setPassword("newpass");
    EXPECT_TRUE(u.verificaPassword("newpass"));
    EXPECT_FALSE(u.verificaPassword("pass"));
}
