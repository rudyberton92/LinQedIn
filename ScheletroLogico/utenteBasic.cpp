#include "utenteBasic.h"

UtBasic::UtBasic() {}

UtBasic::UtBasic(const Username& usnm,const Profilo& pr, Rete* rt, string tipAcc): Utente(usnm, pr, rt, tipAcc) {}

UtBasic::UtBasic(const UtBasic& ut): Utente(ut) {}

UtBasic::~UtBasic() {}

string UtBasic::ricercaUt(string usnm, const Database& db) const {
    string risultato;
    try {
        Utente* ut=db.cercaUt(usnm);
        if(ut) {
            risultato="NOME: "+((ut->getProfilo()).getNome())+"\n"+
                    "COGNOME: "+((ut->getProfilo()).getCognome())+"\n"+
                    "DATA DI NASCITA: "+((ut->getProfilo()).getData())+"\n"+
                    "EMAIL: "+((ut->getProfilo()).getEmail())+"\n\n";
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





