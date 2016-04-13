#include "errori.h"

Errore::Errore(TipoErrore e,string s): err(e), descrizione(s) {}

string Errore::getDescrizione() const{
    return descrizione;
}

string Errore::getTipoErr() const{
    string risultato;
    switch(err){
    case DatiUtente:
        risultato="Errore con i dati";
        break;

    case FileDB:
        risultato="Errore con il file del database";
        break;

    case Ricerca:
        risultato="Ricerca fallita";
        break;

    case Autenticazione:
        risultato="Autenticazione fallita";
        break;

    default:
        risultato="Errore non identificato";
    }

    return risultato;
}

string Errore::mostraErrore() const {
    return getTipoErr()+": "+getDescrizione();
}
