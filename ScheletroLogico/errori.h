#ifndef ERRORI_H
#define ERRORI_H

#include <string>
using std::string;

enum TipoErrore {DatiUtente, FileDB, Ricerca, Autenticazione };

class Errore {
private:
    TipoErrore err;
    string descrizione;

public:
    Errore(TipoErrore,string);
    string getDescrizione() const;
    string getTipoErr() const;
    string mostraErrore() const;
};

#endif
