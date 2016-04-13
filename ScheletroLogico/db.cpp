#include <fstream>
#include <iostream>
#include <stdio.h>

#include "db.h"
#include "utenteBasic.h"
#include "utenteBusiness.h"
#include "utenteExecutive.h"

using std::ofstream;
using std::ifstream;
using std::ios;


void Database::salva() const {
    ofstream OUT("FileDB.txt", ios::app);
    if(OUT) {
        remove("FileDB.txt");
    }
    vector<Utente*>::const_iterator iter=dbUt.begin();
    for(;iter!=dbUt.end();++iter) {
        (*iter)->stampaUtente();
    }
    OUT<<"\n";
    OUT.close();
}


void Database::carica() {
    ifstream IN("FileDB.txt");
    if(!IN){
        throw Errore(FileDB,"non è possibile aprire il file");
    }
    else {
        string usnm, pw;
        string nm,cgnm,dtNas,em,tit,lin,comp,esp;
        string tipoAcc;

        Utente* nuovoUt=0;
        Rete* punt=0;
        string lettura;
        svuotaDB();

        while(IN>>lettura) {
            Rete reteAux;
            IN.ignore(20,':'); //Dati accesso
            getline(IN,usnm,'%');
            getline(IN,pw,'$');

            Username username(usnm,pw);

            IN.ignore(20,':'); //Profilo
            getline(IN,nm,'%');
            getline(IN,cgnm,'%');
            getline(IN,dtNas,'%');
            getline(IN,em,'%');
            Profilo profilo(nm,cgnm,dtNas,em);

            while(IN.get()!='$'){
                getline(IN,tit,'%');
                profilo.aggiungiTitoli(tit);
            }

            while(IN.get()!='$'){
                getline(IN,lin,'%');
                profilo.aggiungiLingue(lin);
            }

            while(IN.get()!='$'){
                getline(IN,comp,'%');
                profilo.aggiungiCompetenze(comp);
            }

            while(IN.get()!='$'){
                getline(IN,esp,'%');
                profilo.aggiungiEsperienze(esp);
            }

            IN.ignore(20,':'); //Contatti
            while(IN.get()!='$'){
                string contatto;
                getline(IN,contatto,'%');

                if(contatto!="nessuno") {
                    reteAux.aggiungi(contatto);
                }
            }
            punt=new Rete(reteAux);

            IN.ignore(20,':'); //Tipologia Account
            getline(IN,tipoAcc,'$');
            if (tipoAcc=="basic") {
                nuovoUt= new UtBasic(username,profilo,punt);
            }
            else {
                if(tipoAcc=="business"){
                    nuovoUt= new UtBusiness(username, profilo,punt);
                }
                else {	//tipoAcc=="executive"
                    nuovoUt= new UtExecutive(username,profilo,punt);
                }
            }
            IN.ignore(5,'^');
            dbUt.push_back(nuovoUt);
        }
    }
    IN.close();
}	


vector<Utente*> Database::getDatabase() const {
    return dbUt;
}


Utente* Database::cercaUt(const string& ut) const {
    vector<Utente*>::const_iterator iter=dbUt.begin();
    while(iter!=dbUt.end()){
        if(((*iter)->getUsername()).getLogin()==ut) {
            return *iter;
        }
        else {
            ++iter;
        }
    }
    return 0;
}


Database::~Database() {
    vector<Utente*>::iterator iter=dbUt.begin();
    while(iter!=dbUt.end()) {
        delete *iter;
        ++iter;
    }
    dbUt.clear();
}


void Database::svuotaDB() {
    vector<Utente*>::iterator iter=dbUt.begin();
    while(iter!=dbUt.end()) {
        delete *iter;
        ++iter;
    }
    dbUt.clear();
}

