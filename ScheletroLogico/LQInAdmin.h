#ifndef LQIN_ADMIN_H
#define LQIN_ADMIN_H

#include "db.h"
#include "username.h"
#include "utente.h"
#include "errori.h"

class LinQedInAdmin {

private:
    Database* db;
    static const Username utenteAdmin;

public:
    LinQedInAdmin(const string&, const string&);
    ~LinQedInAdmin();
    void salvaDBAdmin() const;
    void caricaDBAdmin();
    void cambioAccount(const string&, const string&);
    void inserisciUt(Utente*);
    void rimuoviUt(const string&);
    Database* getDB() const;
    list<Utente*> ricercaNomeCognome(const string&, const string&) const;
    Utente* ricercaUsername(const string&) const;
};

#endif
