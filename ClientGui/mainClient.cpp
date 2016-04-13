#include "mainClient.h"
#include "modProfiloClient.h"
#include "gestisciReteClient.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QPushButton>
#include <QFont>
#include <QString>
#include <QMessageBox>

mainClient::mainClient(const string& us, const string& pw, QMainWindow* from) : pagPadre(from) {
    try {
        client=new LinQedInClient(us,pw);
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

        QPushButton* mostraPr=new QPushButton("Visualizza il profilo",this);
        mostraPr->setGeometry(40,70,150,30);
        mostraPr->setStyleSheet("background-color:white;");

        QPushButton* modificaPr=new QPushButton("Modifica il profilo",this);
        modificaPr->setGeometry(215,70,150,30);
        modificaPr->setStyleSheet("background-color:white;");

        QPushButton* modificaCont=new QPushButton("Gestisci i tuoi contatti",this);
        modificaCont->setGeometry(390,70,170,30);
        modificaCont->setStyleSheet("background-color:white;");

        areaRisultato=new QScrollArea(this);
        areaRisultato->setGeometry(30,115,540,220);
        areaRisultato->setStyleSheet("background-color:white;");
        areaRisultato->setFrameShadow(QFrame::Raised);
        areaRisultato->setFrameShape(QFrame::WinPanel);
        areaRisultato->setLineWidth(1);
        areaRisultato->setWidgetResizable(true);

        output=new QLabel(areaRisultato);
        output->setAlignment(Qt::AlignTop);
        output->setMargin(5);

        QLabel* indicazione=new QLabel("Inserire lo username dell'utente che si desidera cercare:",this);
        indicazione->setGeometry(30,350,500,25);

        campo=new QLineEdit(this);
        campo->setGeometry(30,380,400,30);
        campo->setStyleSheet("background-color:white;");

        QPushButton* ricerca=new QPushButton("Cerca",this);
        ricerca->setGeometry(450,380,100,30);
        ricerca->setStyleSheet("background-color:white;");

        connect(logout,SIGNAL(released()),this,SLOT(logOut()));
        connect(mostraPr,SIGNAL(released()),this,SLOT(mostraProfilo()));
        connect(modificaPr,SIGNAL(released()),this,SLOT(modificaProfilo()));
        connect(modificaCont,SIGNAL(released()),this,SLOT(gestisciContatti()));
        connect(ricerca,SIGNAL(released()),this,SLOT(ricerca()));
    }
    catch(Errore err) {
        throw(err);
    }


}

mainClient::~mainClient(){
    if(client)
        delete client;
}


void mainClient::logOut() {
    this->close();
    pagPadre->show();
}

void mainClient::mostraProfilo() {
    output->clear();
    string profilo=client->getUt()->mostraPrCompleto()+"\n";
    QString pr=QString::fromStdString(profilo);
    output->setText(pr);
    output->setWordWrap(true);

    areaRisultato->setWidget(output);
    areaRisultato->ensureWidgetVisible(output);
    areaRisultato->show();
}

void mainClient::ricerca() {
    QString dato=campo->text();
    if(dato.isEmpty()) {
        QMessageBox msg;
        msg.setText("Per eseguire la ricerca è necessario inserire uno username!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else {
        campo->clear();
        string ut=dato.toStdString();
        try {
            string risultato=client->ricercaContatto(ut);
            QString pr=QString::fromStdString(risultato);
            output->setText(pr);
            output->setWordWrap(true);

            areaRisultato->setWidget(output);
            areaRisultato->ensureWidgetVisible(output);
            areaRisultato->show();
        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }

}


void mainClient::modificaProfilo() {
    output->clear();
    ModificaProfilo* modifica=new ModificaProfilo(client,this);
    modifica->show();
}


void mainClient::gestisciContatti() {
    output->clear();
    GestisciContatti* gestisci=new GestisciContatti(client,this);
    gestisci->show();

}
