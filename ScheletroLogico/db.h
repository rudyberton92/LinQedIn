#ifndef DB_H
#define DB_H

#include "utente.h"
#include "username.h"
#include "profilo.h"
#include "rete.h"
#include "errori.h"
#include <vector>
using std::vector;

class Utente;

class Database {
    friend class LinQedInAdmin;
private:
    vector<Utente*> dbUt;

public:
    void salva() const;
    void carica();
    Utente* cercaUt(const string&) const;
    vector<Utente*> getDatabase() const;
    void svuotaDB();
    ~Database();

};

#endif




