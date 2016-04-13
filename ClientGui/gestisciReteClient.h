#ifndef GESTISCIRETECLIENT_H
#define GESTISCIRETECLIENT_H

#include "mainClient.h"
#include "ScheletroLogico/LQInClient.h"
#include <QListWidget>
#include <QPushButton>

class GestisciContatti: public QMainWindow {
    Q_OBJECT

public:
    explicit GestisciContatti(LinQedInClient*, mainClient*);
    ~GestisciContatti();

private:
    LinQedInClient* client;
    mainClient* pagPadre;
    QListWidget*  elenco,*elenco2;
    QPushButton* elimina,* aggiungi;

private slots:
    void attivaAggiungi();
    void attivaElimina();
    void aggiungiCont();
    void eliminaCont();
    void annulla();
};

#endif
