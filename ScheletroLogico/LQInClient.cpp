#include "LQInClient.h"

LinQedInClient::LinQedInClient(const string& usnm, const string& pw) {
    try {
        db=new Database();
        db->carica();
    }
    catch (Errore err) {
        throw err;
    }

    Utente* risultatoUt= db->cercaUt(usnm);
    if(risultatoUt && (risultatoUt->getUsername()).contrPassword(pw)) {
        ut=risultatoUt;
    }
    else
        throw Errore(Autenticazione,"username e/o password non corretta");
}

LinQedInClient::~LinQedInClient() {
    if(db) {
        delete db;
    }

}

void LinQedInClient::inserisciContRete(const string& usnm) {
    if((ut->getRete())->contattoPresente(usnm)){
        throw Errore(DatiUtente,"l'utente che si desidera inserire tra i propri contatti è già presente");
    }
    else {
        if(db->cercaUt(usnm)){
            ut->getRete()->aggiungi(usnm);
        }
        else {
            throw Errore(Ricerca,"l'utente che si desidera inserire non è presente nel database");
        }
    }
    salvaDBClient();
}

void LinQedInClient::rimuoviContRete(const string& usnm) {
    if(!(ut->getRete())->contattoPresente(usnm)){
        throw Errore(Ricerca,"l'utente che si desidera eliminare dai propri contatti non è presente");
    }
    else {
        (ut->getRete())->rimuovi(usnm);
    }
    salvaDBClient();
}

string LinQedInClient::ricercaContatto(const string& usnm) {
    try {
        return ut->ricercaUt(usnm,*db);
    }
    catch (Errore err){
        throw err;
    }

}

void LinQedInClient::salvaDBClient() const {
    db->salva();
}

void LinQedInClient::caricaDBClient() {
    try {
        db->carica();
    }
    catch (Errore err) {
        throw err;
    }
}

void LinQedInClient::cambiaEmail(const string& em) {
    ut->modificaEmail(em);
}

void LinQedInClient::cambiaPassword(const string& pw) {
    ut->modificaPassword(pw);
}

void LinQedInClient::aggiungiTitoli(const string& tit) {
    ut->aggiungiTitoli(tit);
}

void LinQedInClient::aggiungiLingue(const string& lin){
    ut->aggiungiLingue(lin);
}

void LinQedInClient::aggiungiCompetenze(const string& comp) {
    ut->aggiungiCompetenze(comp);
}

void LinQedInClient::aggiungiEsperienze(const string& esp) {
    ut->aggiungiEsperienze(esp);
}

void LinQedInClient::eliminaTitoli(int n){
    try {
        ut->eliminaTitoli(n);
    }
    catch (Errore err){
        throw err;
    }
}

void LinQedInClient::eliminaLingue(int n) {
    try {
        ut->eliminaLingue(n);
    }
    catch (Errore err){
        throw err;
    }
}

void LinQedInClient::eliminaCompetenze(int n) {
    try {
        ut->eliminaCompetenze(n);
    }
    catch (Errore err){
        throw err;
    }
}

void LinQedInClient::eliminaEsperienze(int n) {
    try {
        ut->eliminaEsperienze(n);
    }
    catch (Errore err){
        throw err;
    }
}

Utente* LinQedInClient::getUt() const {
    return ut;
}

Database* LinQedInClient::getDb() const{
    return db;
}

