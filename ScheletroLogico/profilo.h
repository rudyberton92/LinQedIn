#ifndef PROFILO_H
#define PROFILO_H

#include <string>
#include <vector>
#include <fstream>
#include "errori.h"
using std::string;
using std::vector;



class Profilo {
private:
    string nome;
    string cognome;
    string dataNascita;
    string email;
    vector<string> titoliStudio;
    vector<string> lingue;
    vector<string> competenzeLav;
    vector<string> esperienzeProf;

public:
    Profilo();
    Profilo(string,string, string,string);
    Profilo(const Profilo&);
    void stampaProfilo() const;
    string getNome() const;
    string getCognome() const;
    string getData() const;
    string getEmail() const;
    vector<string> getTitoli() const;
    vector<string> getLingue() const;
    vector<string> getCompetenze() const;
    vector<string> getEsperienze() const;
    string mostraTitoli() const;
    string mostraLingue() const;
    string mostraCompetenze() const;
    string mostraEsperienze() const;
    void modificaEmail(const string&);
    void aggiungiTitoli(const string&);
    void aggiungiLingue(const string&);
    void aggiungiCompetenze(const string&);
    void aggiungiEsperienze(const string&);
    void eliminaTitoli(int);
    void eliminaLingue(int);
    void eliminaCompetenze(int);
    void eliminaEsperienze(int);
};

#endif
