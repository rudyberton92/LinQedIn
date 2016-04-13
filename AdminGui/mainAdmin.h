#ifndef MAINADMIN_H
#define MAINADMIN_H

#include "ScheletroLogico/LQInAdmin.h"
#include <QMainWindow>
#include <string>
#include <QScrollArea>
using std::string;

class mainAdmin: public QMainWindow {
    Q_OBJECT

public:
    explicit mainAdmin(const string&, const string&, QMainWindow*);
    ~mainAdmin();

private:
    QMainWindow* pagPadre;
    QScrollArea* areaRisultati;
    LinQedInAdmin* admin;


private slots:
    void logOut();
    void ricerca();
    void inserimento();
    void rimozione();
    void cambioAccount();

};

#endif
