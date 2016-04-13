#ifndef MAINCLIENT_H
#define MAINCLIENT_H

#include "ScheletroLogico/LQInClient.h"
#include <QMainWindow>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>


class mainClient: public QMainWindow {
    Q_OBJECT

public:
    explicit mainClient(const string&, const string&, QMainWindow*);
    ~mainClient();


private:
    QMainWindow* pagPadre;
    QScrollArea* areaRisultato;
    LinQedInClient* client;
    QLineEdit* campo;
    QLabel* output;

private slots:
    void logOut();
    void ricerca();
    void modificaProfilo();
    void gestisciContatti();
    void mostraProfilo();

};

#endif
