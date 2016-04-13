#ifndef RIMOZIONEADMIN_H
#define RIMOZIONEADMIN_H

#include "mainAdmin.h"
#include "ScheletroLogico/LQInAdmin.h"

#include <QLineEdit>
#include <QScrollArea>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

class RimozioneUt: public QMainWindow {
    Q_OBJECT

public:
    explicit RimozioneUt(LinQedInAdmin*, mainAdmin*, QScrollArea* );
    ~RimozioneUt();

private:
    LinQedInAdmin* admin;
    mainAdmin* pagPadre;
    QScrollArea* areaRisultato;
    QLineEdit* campo;
    QListWidget* elenco;
    QPushButton* elimina;
    QLabel* output;

private slots:
    void rimuovi();
    void annulla();
    void attivaPulsante();

};
#endif
