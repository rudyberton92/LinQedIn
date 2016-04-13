#ifndef LQIN_CLIENT_H
#define LQIN_CLIENT_H

#include "db.h"
#include "utente.h"
#include "errori.h"

class LinQedInClient {
private:
    Database* db;
    Utente* ut;

public:
    LinQedInClient(const string&, const string&);
    ~LinQedInClient();
    Utente* getUt() const;
    Database* getDb() const;
    void inserisciContRete(const string&);
    void rimuoviContRete(const string&);
    string ricercaContatto(const string&);
    void salvaDBClient() const;
    void caricaDBClient();
    void cambiaEmail(const string&);
    void cambiaPassword(const string&);
    void aggiungiTitoli(const string&);
    void aggiungiLingue(const string&);
    void aggiungiCompetenze(const string&);
    void aggiungiEsperienze(const string&);
    void eliminaTitoli(int);
    void eliminaLingue(int);
    void eliminaCompetenze(int);
    void eliminaEsperienze(int);
};

#endif
