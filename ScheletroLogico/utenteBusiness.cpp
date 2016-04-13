#include "utenteBusiness.h"

UtBusiness::UtBusiness() {}

UtBusiness::UtBusiness(const Username& usnm,const Profilo& pr, Rete* rt,string tipAcc): UtBasic(usnm,pr,rt,tipAcc) {}

UtBusiness::UtBusiness(const UtBusiness& ut): UtBasic(ut) {}

UtBusiness::~UtBusiness(){}

string UtBusiness::ricercaUt(string usnm, const Database& db) const {
    string risultato;
    try {
        risultato=UtBasic::ricercaUt(usnm,db);
        Utente* ut=db.cercaUt(usnm);
        if(ut) {
            risultato=risultato+"TITOLI SI STUDIO: "+((ut->getProfilo()).mostraTitoli())+"\n"+
                    "LINGUE CONOSCIUTE: "+((ut->getProfilo()).mostraLingue())+"\n"+
                    "COMPETENZE LAVORATIVE: "+((ut->getProfilo()).mostraCompetenze())+"\n"+
                    "ESPERIENZE PROFESSIONALI: "+((ut->getProfilo()).mostraEsperienze())+"\n";
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

