#ifndef UTENTE_H
#define UTENTE_H

#include "profilo.h"
#include "username.h"
#include "rete.h"
#include "db.h"
#include "errori.h"

class Database;

class Utente { //classe base polimorfa e astratta
private:
    Username us;
    Profilo prof;
    Rete* rete;
    string tipoAccount;

public:
    Utente();
    Utente(const Username&, const Profilo&, Rete* =0, string ="basic");
    Utente(const Utente&);
    virtual string ricercaUt(string,const Database&) const =0;
    virtual ~Utente();
    string mostraDatiAccesso() const;
    string mostraPrCompleto() const;
    void stampaUtente() const;
    const Username& getUsername() const;
    const Profilo& getProfilo() const;
    Rete* getRete() const;
    string getTipoAcc() const;
    void cambiaTipoAcc(const string&);
    void modificaEmail(const string&);
    void modificaPassword(const string&);
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
