#ifndef INSERIMENTOADMIN_H
#define INSERIMENTOADMIN_H

#include "mainAdmin.h"
#include "ScheletroLogico/LQInAdmin.h"
#include "ScheletroLogico/username.h"
#include "ScheletroLogico/profilo.h"
#include "ScheletroLogico/utente.h"
#include "ScheletroLogico/utenteBasic.h"
#include "ScheletroLogico/utenteBusiness.h"
#include "ScheletroLogico/utenteExecutive.h"

#include <QScrollArea>
#include <QLineEdit>
#include <QRadioButton>




class InserimentoUt: public QMainWindow {
    Q_OBJECT

public:
    explicit InserimentoUt(LinQedInAdmin*, mainAdmin*, QScrollArea* );
    ~InserimentoUt();

private:
    LinQedInAdmin* admin;
    mainAdmin* pagPadre;
    QScrollArea* areaRisultato;
    QLineEdit* us,* pw,* nm,* cg,*dtN,* em;
    QRadioButton* basic,* business,*executive;

private slots:
    void annulla();
    void inserisci();

};

#endif
