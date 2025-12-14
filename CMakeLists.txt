cmake_minimum_required(VERSION 3.30)
project(ProgettoLabProgrammazione)

set(CMAKE_CXX_STANDARD 26)

add_executable(ProgettoLabProgrammazione main.cpp
        ContoCorrente.cpp
        ContoCorrente.h
        Utente.cpp
        Utente.h
        Banca.cpp
        Banca.h
        Transazione.cpp
        Transazione.h
        TransactionFactory.cpp
        TransactionFactory.h
        DataStoreCSV.cpp
        DataStoreCSV.h)

set(CORE_SOURCES
        Banca.cpp
        Utente.cpp
        ContoCorrente.cpp
        Transazione.cpp
        TransactionFactory.cpp
        DataStoreCSV.cpp
)

add_library(core ${CORE_SOURCES})

target_link_libraries(ProgettoLabProgrammazione core)

add_subdirectory(test)