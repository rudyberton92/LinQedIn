#ifndef RICERCAADMIN_H
#define RICERCAADMIN_H

#include "mainAdmin.h"
#include "ScheletroLogico/LQInAdmin.h"

#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QFrame>

class RicercaUt: public QMainWindow {
    Q_OBJECT

public:
    explicit RicercaUt(LinQedInAdmin*, mainAdmin*, QScrollArea* );
    ~RicercaUt();

private:
    LinQedInAdmin* admin;
    mainAdmin* pagPadre;
    QScrollArea* areaRisultato;
    QRadioButton* rUs, *rNmCg;
    QLineEdit* campo,* campo1;
    QLabel* output;
    QFrame* areaForm;

private slots:
    void cerca();
    void annulla();
    void mostraCampo();

};

#endif // RICERCAADMIN_H
