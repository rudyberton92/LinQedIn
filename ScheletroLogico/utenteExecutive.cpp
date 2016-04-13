#include "utenteExecutive.h"

UtExecutive::UtExecutive() {}

UtExecutive::UtExecutive(const Username& usnm,const Profilo& pr, Rete* rt, string tipAcc): UtBusiness(usnm,pr,rt,tipAcc) {}

UtExecutive::UtExecutive(const UtExecutive& ut): UtBusiness(ut) {}

UtExecutive::~UtExecutive() {}

string UtExecutive::ricercaUt(string usnm, const Database& db) const {
    string risultato;
    try {
        risultato=UtBusiness::ricercaUt(usnm,db);
        Utente* ut=db.cercaUt(usnm);
        if(ut) {
            risultato=risultato+"RETE DI CONTATTI: "+((ut->getRete())->visualizzaRete())+"\n";
            return risultato;
        }
        else{
            throw Errore(Ricerca,"l'utente cercato non è registrato in LinQedIn!");
        }

    }
    catch (Errore err) {
        throw err;
    }

}
