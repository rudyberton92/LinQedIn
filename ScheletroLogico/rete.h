#ifndef RETE_H
#define RETE_H

#include <list>
#include <string>
#include "username.h"
using std::list;

class Rete {
private:
    list<string> reteContatti;

public:
    Rete();
    Rete(const Rete&);
    void aggiungi(const string&);
    void rimuovi(const string&);
    string visualizzaRete() const;
    void eliminaRete();
    bool contattoPresente(const string&) const;
    void stampaRete() const;
    list<string> getReteContatti();
};

#endif
