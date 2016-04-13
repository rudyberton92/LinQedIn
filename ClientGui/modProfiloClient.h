#ifndef MODIFICAPROFILO_H
#define MODIFICAPROFILO_H

#include "mainClient.h"
#include "ScheletroLogico/LQInClient.h"

#include <QListWidget>
#include <QFrame>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class ModificaProfilo: public QMainWindow {
    Q_OBJECT

public:
    explicit ModificaProfilo(LinQedInClient*, mainClient*);
    ~ModificaProfilo();


private:
    LinQedInClient* client;
    mainClient* pagPadre;
    QListWidget*  elenco;
    QFrame* cornice;
    QTextEdit* campo;
    QPushButton* emPw,* tit,*lin, *comp,*esp,* elimina;
    QLineEdit* em, *pw, *confPw;

private slots:

    void tornaIndietro();
    void modEmPw();
    void modificaEm();
    void modificaPw();
    void modifica();
    void aggiungiDato();
    void eliminaDato();
    void annulla();
    void attivaPulsante();
};


#endif // MODIFICAPROFILO_H
