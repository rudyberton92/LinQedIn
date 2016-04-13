#include "utente.h"
#include <fstream>

using std::ios;
using std::ofstream; 

Utente::Utente() {}

Utente::Utente(const Username& usnm, const Profilo& pr, Rete* rt, string tipAcc):  us(usnm), prof(pr), tipoAccount(tipAcc){
    if(rt)
        rete=new Rete(*rt);
    else
        rete=0;
}

Utente::Utente(const Utente& ut): us(ut.us), prof(ut.prof), tipoAccount(ut.tipoAccount) {
    if(ut.rete)
        rete=new Rete(*(ut.rete));
    else
        rete=0;
}

Utente::~Utente() {
    if(rete){
        rete->eliminaRete();
        delete rete;
    }
}

void Utente::stampaUtente() const {
    ofstream OUT("FileDB.txt", ios::app);
    us.Username::stampaUsername();
    prof.Profilo::stampaProfilo();
    if(rete){
        rete->stampaRete();
    }
    else {
        OUT<<"Contatti: nessuno%$"<<"\n";
    }
    OUT<<"Tipologia account:"<<tipoAccount<<"$"<<"\n";
    OUT<<"^"<<"\n";
    OUT.close();
}

const Username& Utente::getUsername() const{
    return us;
}

const Profilo& Utente::getProfilo() const {
    return prof;
}

Rete* Utente::getRete() const {
    if(rete!=0){
        return rete;
    }
    return new Rete();
}

string Utente::mostraDatiAccesso() const {
    string risultato;
    risultato="USERNAME: "+us.getLogin()+"\n"+"PASSWORD: "+us.getPassword()+"\n \n"+"TIPOLOGIA DI ACCOUNT: "+getTipoAcc()+"\n \n";
    return risultato;
}

string Utente::mostraPrCompleto() const {
    string risultato;
    risultato="NOME: "+prof.getNome()+"\n"+"COGNOME: "+prof.getCognome()+"\n"+"DATA DI NASCITA: "+prof.getData()+"\n"+
            "EMAIL: "+prof.getEmail()+"\n \n"+"TITOLI DI STUDIO: "+prof.mostraTitoli()+"\n"+"LINGUE CONOSCIUTE: "+prof.mostraLingue()+"\n"+
            "COMPETENZE LAVORATIVE: "+prof.mostraCompetenze()+"\n"+"ESPERIENZE PROFESSIONALI: "+prof.mostraEsperienze()+"\n"+
            "RETE DI CONTATTI: "+rete->visualizzaRete();
    return risultato;
}


string Utente::getTipoAcc() const {
    return tipoAccount;
}

void Utente::modificaEmail(const string& em) {
    prof.modificaEmail(em);
}

void Utente::modificaPassword(const string& pw) {
    us.modificaPassword(pw);
}

void Utente::aggiungiTitoli(const string& tit) {
    prof.aggiungiTitoli(tit);
}

void Utente::aggiungiLingue(const string& lin) {
    prof.aggiungiLingue(lin);
}

void Utente::aggiungiCompetenze(const string& comp) {
    prof.aggiungiCompetenze(comp);
}

void Utente::aggiungiEsperienze(const string& esp) {
    prof.aggiungiEsperienze(esp);
}

void Utente::eliminaTitoli(int n) {
    try {
        prof.eliminaTitoli(n);
    }
    catch (Errore err) {
        throw err;
    }
}

void Utente::eliminaLingue(int n) {
    try {
        prof.eliminaLingue(n);
    }
    catch (Errore err) {
        throw err;
    }
}

void Utente::eliminaCompetenze(int n) {
    try {
        prof.eliminaCompetenze(n);
    }
    catch (Errore err) {
        throw err;
    }
}

void Utente::eliminaEsperienze(int n) {
    try {
        prof.eliminaEsperienze(n);
    }
    catch (Errore err) {
        throw err;
    }
}

void Utente::cambiaTipoAcc(const string& acc) {
    tipoAccount=acc;
}
