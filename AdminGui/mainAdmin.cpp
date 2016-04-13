#include "mainAdmin.h"
#include "ricercaAdmin.h"
#include "inserimentoAdmin.h"
#include "rimozioneAdmin.h"
#include "cambioAccAdmin.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QPushButton>
#include <QFont>
#include <QMessageBox>
#include <QLabel>


mainAdmin::mainAdmin(const string& us, const string& pw, QMainWindow* from) :pagPadre(from) {
    try {
        admin=new LinQedInAdmin(us,pw);

        this->setStyleSheet("background-color:lightblue;");
        this->setFixedSize(600, 430);
        QRect screenGeometry=QApplication::desktop()->screenGeometry();
        int x=(screenGeometry.width()-width())/2;
        int y=(screenGeometry.height()-height())/2;
        move(x,y);

        QLabel* titolo= new QLabel(this);
        titolo->setText("LinQedIn");
        titolo->setGeometry(20,15,200,30);
        QFont font("Ubuntu",20, QFont::Bold);
        titolo->setFont(font);

        QPushButton* logout=new QPushButton("LogOut",this);
        logout->setGeometry(490,20,90,30);
        logout->setStyleSheet("background-color:blue;color:white; font-weight:bold;");


        QPushButton* cerca=new QPushButton("Cerca utente",this);
        cerca->setGeometry(400,110,170,35);
        cerca->setStyleSheet("background-color:white;");

        QPushButton* inserisci=new QPushButton("Inserisci utente",this);
        inserisci->setGeometry(400,180,170,35);
        inserisci->setStyleSheet("background-color:white;");

        QPushButton* rimuovi=new QPushButton("Rimuovi utente",this);
        rimuovi->setGeometry(400,250,170,35);
        rimuovi->setStyleSheet("background-color:white;");

        QPushButton* cambiaAcc=new QPushButton("Cambia account utente",this);
        cambiaAcc->setGeometry(400,320,170,35);
        cambiaAcc->setStyleSheet("background-color:white;");


        connect(logout,SIGNAL(released()),this,SLOT(logOut()));
        connect(cerca,SIGNAL(released()),this,SLOT(ricerca()));
        connect(inserisci,SIGNAL(released()),this,SLOT(inserimento()));
        connect(rimuovi,SIGNAL(released()),this,SLOT(rimozione()));
        connect(cambiaAcc,SIGNAL(released()),this,SLOT(cambioAccount()));

        areaRisultati=new QScrollArea(this);

        areaRisultati->setGeometry(30,60,330,350);
        areaRisultati->setStyleSheet("background-color:white;");
        areaRisultati->setFrameShadow(QFrame::Raised);
        areaRisultati->setFrameShape(QFrame::WinPanel);
        areaRisultati->setLineWidth(1);


    }
    catch(Errore err) {
        throw(err);
    }


}

mainAdmin::~mainAdmin(){
    if(admin)
        delete admin;
    if(pagPadre)
        delete pagPadre;
}


void mainAdmin::logOut() {
    this->close();
    pagPadre->show();
}

void mainAdmin::ricerca() {
    try {
        admin->caricaDBAdmin();
        RicercaUt* cerca= new RicercaUt(admin,this,areaRisultati);
        cerca->show();
    }
    catch(Errore err){
        QMessageBox msg;
        msg.setText(err.mostraErrore().data());
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}


void mainAdmin::inserimento() {
    try {
        admin->caricaDBAdmin();
        InserimentoUt* inserisci=new InserimentoUt(admin,this,areaRisultati);
        inserisci->show();
    }
    catch(Errore err){
        QMessageBox msg;
        msg.setText(err.mostraErrore().data());
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}

void mainAdmin::rimozione() {
    try {
        admin->caricaDBAdmin();
        RimozioneUt* rimuovi=new RimozioneUt(admin,this,areaRisultati);
        rimuovi->show();
    }
    catch(Errore err){
        QMessageBox msg;
        msg.setText(err.mostraErrore().data());
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}

void mainAdmin::cambioAccount() {
    try {
        admin->caricaDBAdmin();
        CambioAccUt* cambiaAcc=new CambioAccUt(admin,this,areaRisultati);
        cambiaAcc->show();
    }
    catch(Errore err){
        QMessageBox msg;
        msg.setText(err.mostraErrore().data());
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}
