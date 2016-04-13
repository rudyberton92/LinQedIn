#include "rete.h"
#include <fstream>

using std::ofstream;
using std::ios;

Rete::Rete(){}

Rete::Rete(const Rete& r){
    if(!r.reteContatti.empty()) {
        list<string>::const_iterator iter=r.reteContatti.begin();
        for(;iter!=r.reteContatti.end();++iter) {
            reteContatti.push_back(*iter);
        }
    }
}

void Rete::aggiungi(const string& con) {
    reteContatti.push_back(con);
}

void Rete::rimuovi(const string& con) {
    list<string>::iterator iter=reteContatti.begin();
    bool stop=false;
    while(iter!=reteContatti.end() && stop==false) {
        if(*iter==con) {
            reteContatti.erase(iter);
            stop=true;
        }
        ++iter;
    }
}

string Rete::visualizzaRete() const {
    list<string>::const_iterator iter=reteContatti.begin();
    string risultato;
    if(reteContatti.empty()) {
        risultato="nessuno";
    }
    else {
        while(iter!=reteContatti.end()){
            risultato=risultato+(*iter)+"; ";
            ++iter;
        }
    }
    return risultato;
}

void Rete::eliminaRete() {
    if(!reteContatti.empty()){
        reteContatti.clear();
    }
}

bool Rete::contattoPresente(const string& login) const {
    list<string>::const_iterator iter=reteContatti.begin();
    while(iter!=reteContatti.end()) {
        if(*iter==login) {
            return true;
        }
        ++iter;
    }
    return false;
}


void Rete::stampaRete() const {
    ofstream OUT("FileDB.txt", ios::app);
    list<string>::const_iterator iter=reteContatti.begin();
    string risultato;
    while(iter!=reteContatti.end()){
        risultato=risultato+" "+(*iter)+"%";
        ++iter;
    }
    OUT<<"Contatti:"<<risultato<<"$"<<"\n";
    OUT.close();
}

list<string> Rete::getReteContatti() {
    return reteContatti;
}
