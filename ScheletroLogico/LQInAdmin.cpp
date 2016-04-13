#include "LQInAdmin.h"
#include "utenteBasic.h"
#include "utenteBusiness.h"
#include "utenteExecutive.h"

const Username LinQedInAdmin::utenteAdmin("rberton","rb123");

LinQedInAdmin::LinQedInAdmin (const string& us, const string& pw) {
    if(utenteAdmin==Username(us,pw)){
        try{
            db=new Database();
            caricaDBAdmin();
        }
        catch (Errore err) {
            throw err;
        }
    }
    else { //l'utente non è amministratore
        throw Errore(Autenticazione,"username e/o password non corretta");
    }
}

LinQedInAdmin::~LinQedInAdmin() {
    delete db;
}

void LinQedInAdmin::inserisciUt(Utente* ut) {
    string us=(ut->getUsername()).getLogin();
    Utente* utTrovato=ricercaUsername(us);
    if(!utTrovato) {
        db->dbUt.push_back(ut);
        salvaDBAdmin();
    }
    else {
        throw Errore(Ricerca,"username già utilizzato da un utente presente nel database");
    }
}

void LinQedInAdmin::rimuoviUt(const string& ut) {
    vector<Utente*>::iterator iter=db->dbUt.begin();
    bool trovato=false;
    while(iter!=db->dbUt.end() && trovato==false){
        if(((*iter)->getUsername()).getLogin()==ut) {
            delete *iter;
            db->dbUt.erase(iter);
            trovato=true;
            vector<Utente*>::iterator it=db->dbUt.begin();
            while(it!=db->dbUt.end()) {
                Rete* reteContatti=(*it)->getRete();
                if (reteContatti && reteContatti->contattoPresente(ut)) {
                    reteContatti->rimuovi(ut);
                }
                ++it;
            }


            salvaDBAdmin();
            return;
        }
        else{
            ++iter;
        }
    }
    if(iter==db->dbUt.end()) { //l'utente da eliminare non è stato trovato
        throw Errore(Ricerca, "l'utente che si vuole eliminare non è presente nel database!" );
    }
}

void LinQedInAdmin::salvaDBAdmin() const {
    db->salva();
}

void LinQedInAdmin::caricaDBAdmin() {
    try {
        db->carica();
    }
    catch (Errore err) {
        throw err;
    }
}

void LinQedInAdmin::cambioAccount(const string& user, const string& tipoAcc) {
    Utente* punt=db->cercaUt(user);
    string tipo=punt->getTipoAcc();

    if(punt) {
        if(tipoAcc=="basic" && tipo!="basic") {
            UtBasic* nuovoPunt= new UtBasic(*(dynamic_cast<UtBasic*>(punt)));
            nuovoPunt->cambiaTipoAcc("basic");
            try {
                rimuoviUt(user);
                inserisciUt(nuovoPunt);
            }
            catch (Errore err) {
                throw err;
            }
        }
        else {
            if(tipoAcc=="business" && tipo!="business") {
                if(tipo=="basic") {
                    UtBusiness* nuovoPunt=new UtBusiness(punt->getUsername(),punt->getProfilo(),punt->getRete());
                    nuovoPunt->cambiaTipoAcc("business");
                    try {
                        rimuoviUt(user);
                        inserisciUt(nuovoPunt);
                    }
                    catch (Errore err) {
                        throw err;
                    }
                }

                else { //tipo=="executive"
                    UtBusiness* nuovoPunt= new UtBusiness(*(dynamic_cast<UtBusiness*>(punt)));
                    nuovoPunt->cambiaTipoAcc("business");

                    try {
                        rimuoviUt(user);
                        inserisciUt(nuovoPunt);
                    }
                    catch (Errore err) {
                        throw err;
                    }
                }
            }
            else {//tipoAcc=="executive"
                if(tipo!="executive"){
                    UtExecutive* nuovoPunt= new UtExecutive(punt->getUsername(),punt->getProfilo(),punt->getRete());
                    nuovoPunt->cambiaTipoAcc("executive");
                    try {
                        rimuoviUt(user);
                        inserisciUt(nuovoPunt);
                    }
                    catch (Errore err) {
                        throw err;
                    }
                }
            }
        }

        salvaDBAdmin();
    }
    else {
        throw Errore(Ricerca,"l'utente di cui si sta cambiando i privilegi non compare nel database");
    }
}

list<Utente*> LinQedInAdmin::ricercaNomeCognome(const string& nm, const string& cgnm) const{
    list<Utente*> risultato;
    vector<Utente*> dbUT=db->getDatabase();
    vector<Utente*>::iterator iter=dbUT.begin();
    for(; iter!=dbUT.end(); ++iter) {
        string nome=((*iter)->getProfilo()).getNome();
        string cognome=((*iter)->getProfilo()).getCognome();
        if(nome==nm && cognome==cgnm) {
            risultato.push_back(*iter);
        }
    }
    return risultato;
}

Utente* LinQedInAdmin::ricercaUsername(const string& usnm) const {
    Utente* risultato=db->cercaUt(usnm);
    if(risultato){
        return risultato;
    }
    else
        return 0;
}

Database* LinQedInAdmin::getDB() const {
    return db;
}
