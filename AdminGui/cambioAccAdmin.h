#ifndef CAMBIOACCADMIN_H
#define CAMBIOACCADMIN_H

#include "mainAdmin.h"
#include "ScheletroLogico/LQInAdmin.h"
#include "ScheletroLogico/utente.h"
#include "ScheletroLogico/utenteBasic.h"
#include "ScheletroLogico/utenteBusiness.h"
#include "ScheletroLogico/utenteExecutive.h"

#include <QScrollArea>
#include <QRadioButton>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

class CambioAccUt: public QMainWindow {
    Q_OBJECT

public:
    explicit CambioAccUt(LinQedInAdmin*, mainAdmin*, QScrollArea*);
    ~CambioAccUt();

private:
    LinQedInAdmin* admin;
    mainAdmin* pagPadre;
    QScrollArea* areaRisultato;
    QRadioButton* basic,* business,*executive;
    QListWidget* elenco;
    QLabel* output;
    QPushButton* tastoCambia;

private slots:
    void annulla();
    void cambia();
    void mostraTipologia();

};
#endif
