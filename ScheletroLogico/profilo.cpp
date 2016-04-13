#include "profilo.h"

using std::ofstream;
using std::ios;

Profilo::Profilo() {}

Profilo::Profilo(string nm,string cg, string dn,string em): nome(nm), cognome(cg),
    dataNascita(dn), email(em) {
    titoliStudio.push_back("informazione mancante");
    lingue.push_back("informazione mancante");
    competenzeLav.push_back("informazione mancante");
    esperienzeProf.push_back("informazione mancante");
}

Profilo::Profilo(const Profilo& p): nome(p.nome), cognome(p.cognome), dataNascita(p.dataNascita), email(p.email) {	
    vector<string>::const_iterator iter;
    for(iter=(p.titoliStudio).begin(); iter!=(p.titoliStudio).end(); ++iter){
        titoliStudio.push_back(*iter);
    }
    for(iter=(p.lingue).begin(); iter!=(p.lingue).end(); ++iter){
        lingue.push_back(*iter);
    }
    for(iter=(p.competenzeLav).begin(); iter!=(p.competenzeLav).end(); ++iter){
        competenzeLav.push_back(*iter);
    }
    for(iter=(p.esperienzeProf).begin(); iter!=(p.esperienzeProf).end(); ++iter){
        esperienzeProf.push_back(*iter);
    }
}

void Profilo::stampaProfilo() const {
    ofstream OUT("FileDB.txt", ios::app);
    OUT<<"Profilo:"<<nome<<"%"<<cognome<<"%"<<dataNascita<<"%"<<email<<"%";
    vector<string>::const_iterator iter;
    for(iter=titoliStudio.begin();iter!=titoliStudio.end(); ++iter) {
        OUT<<" "<<*iter<<"%";
    }
    OUT<<"$";

    for(iter=lingue.begin();iter!=lingue.end(); ++iter) {
        OUT<<" "<<*iter<<"%";
    }
    OUT<<"$";

    for(iter=competenzeLav.begin();iter!=competenzeLav.end(); ++iter) {
        OUT<<" "<<*iter<<"%";
    }
    OUT<<"$";

    for(iter=esperienzeProf.begin();iter!=esperienzeProf.end(); ++iter) {
        OUT<<" "<<*iter<<"%";
    }
    OUT<<"$"<<"\n";
    OUT.close();
}

string Profilo::getNome() const {
    return nome;
}

string Profilo::getCognome() const {
    return cognome;
}

string Profilo::getData() const {
    return dataNascita;
}

string Profilo::getEmail() const {
    return email;
}

vector<string> Profilo::getTitoli() const {
    return titoliStudio;
}

vector<string> Profilo::getLingue() const {
    return lingue;
}

vector<string> Profilo::getCompetenze() const {
    return  competenzeLav;
}

vector<string> Profilo::getEsperienze() const {
    return esperienzeProf;
}

string Profilo::mostraTitoli() const {
    string ris="\n ";
    vector<string>::const_iterator iter=titoliStudio.begin();
    while (iter!=titoliStudio.end()) {
        ris=ris+"- "+(*iter)+";\n ";
        ++iter;
    }
    return ris;
}

string Profilo::mostraLingue() const {
    string ris="\n ";
    vector<string>::const_iterator iter=lingue.begin();
    while(iter!=lingue.end()) {
        ris=ris+"- "+(*iter)+";\n ";
        ++iter;
    }
    return ris;
}

string Profilo::mostraCompetenze() const {
    string ris="\n ";
    vector<string>::const_iterator iter=competenzeLav.begin();
    while(iter!=competenzeLav.end()) {
        ris=ris+"- "+(*iter)+";\n ";
        ++iter;
    }
    return ris;
}

string Profilo::mostraEsperienze() const {
    string ris="\n ";
    vector<string>::const_iterator iter=esperienzeProf.begin();
    while(iter!=esperienzeProf.end()) {
        ris=ris+"- "+(*iter)+";\n ";
        ++iter;
    }
    return ris;
}

void Profilo::aggiungiTitoli(const string& tit) {
    vector<string>::iterator iter=titoliStudio.begin();
    if(*iter=="informazione mancante") {
        titoliStudio.clear();
    }
    titoliStudio.push_back(tit);
}

void Profilo::aggiungiLingue(const string& lin) {
    vector<string>::iterator iter=lingue.begin();
    if(*iter=="informazione mancante") {
        lingue.clear();
    }
    lingue.push_back(lin);
}

void Profilo::aggiungiCompetenze(const string& comp) {
    vector<string>::iterator iter=competenzeLav.begin();
    if(*iter=="informazione mancante") {
        competenzeLav.clear();
    }
    competenzeLav.push_back(comp);
}

void Profilo::aggiungiEsperienze(const string& esp) {
    vector<string>::iterator iter=esperienzeProf.begin();
    if(*iter=="informazione mancante") {
        esperienzeProf.clear();
    }
    esperienzeProf.push_back(esp);
}

void Profilo::eliminaTitoli(int n) {
    int dim=titoliStudio.size();
    if(dim>=n) {
        vector<string>::iterator iter=titoliStudio.begin();
        titoliStudio.erase(iter+n);
    }
    else {
        throw Errore(DatiUtente,"non è possibile eliminare il titolo di studi scelto");
    }
}

void Profilo::eliminaLingue(int n) {
    int dim=lingue.size();
    if(dim>=n) {
        vector<string>::iterator iter=lingue.begin();
        lingue.erase(iter+n);
    }
    else {
        throw Errore(DatiUtente,"non è possibile eliminare la lingua scelta");
    }
}

void Profilo::eliminaCompetenze(int n){
    int dim=competenzeLav.size();
    if(dim>=n) {
        vector<string>::iterator iter=competenzeLav.begin();
        competenzeLav.erase(iter+n);
    }
    else {
        throw Errore(DatiUtente,"non è possibile eliminare la competenza scelta");
    }
}

void Profilo::eliminaEsperienze(int n){
    int dim=esperienzeProf.size();
    if(dim>=n) {
        vector<string>::iterator iter=esperienzeProf.begin();
        esperienzeProf.erase(iter+n);
    }
    else {
        throw Errore(DatiUtente,"non è possibile eliminare l'esperienza scelta");
    }
}

void Profilo::modificaEmail(const string& em) {
    email=em;
}
