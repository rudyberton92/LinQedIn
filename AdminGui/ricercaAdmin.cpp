#include "ricercaAdmin.h"

#include <QPushButton>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QString>
#include <QMessageBox>
#include <Qt>
#include <string>
#include <list>

RicercaUt::RicercaUt(LinQedInAdmin* ut, mainAdmin* from, QScrollArea* cornice):
    admin(ut), pagPadre(from), areaRisultato(cornice) {

    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(450, 270);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);


    QLabel* intestazione= new QLabel(this);
    intestazione->setText("Selezionare la modalità di ricerca:");
    intestazione->setGeometry(30,15,250,30);

    rUs=new QRadioButton("Ricerca username",this);
    rNmCg=new QRadioButton("Ricerca Nome e Cognome",this);
    rUs->setGeometry(35,60,150,20);
    rNmCg->setGeometry(210,60,200,20);

    connect(rUs,SIGNAL(clicked(bool)),this,SLOT(mostraCampo()));
    connect(rNmCg,SIGNAL(clicked(bool)),this,SLOT(mostraCampo()));

    QPushButton* trova=new QPushButton("Cerca",this);
    trova->setGeometry(115,220,100,30);
    trova->setStyleSheet("background-color:white;");
    QPushButton* annulla=new QPushButton("Annulla",this);
    annulla->setGeometry(235,220,100,30);
    annulla->setStyleSheet("background-color:white;");

    connect(trova,SIGNAL(released()),this,SLOT(cerca()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}


RicercaUt::~RicercaUt() {
    if(admin)
        delete admin;
    if(pagPadre)
        delete pagPadre;
}

void RicercaUt::mostraCampo() {
    areaForm=new QFrame(this);
    areaForm->setGeometry(0,85,450,130);
    if(rUs->isChecked()) {
        QLabel* info=new QLabel("Username:",areaForm);
        info->setGeometry(30,20,75,30);

        campo=new QLineEdit(areaForm);
        campo->setGeometry(110,20,300,30);
        campo->setStyleSheet("background-color:white;");
    }
    else {
        QLabel* info1=new QLabel("Nome*:",areaForm);
        info1->setGeometry(30,20,70,30);
        QLabel* info2=new QLabel("Cognome*:",areaForm);
        info2->setGeometry(30,60,80,30);

        campo=new QLineEdit(areaForm);
        campo->setGeometry(110,20,300,30);
        campo->setStyleSheet("background-color:white;");

        campo1=new QLineEdit(areaForm);
        campo1->setGeometry(110,60,300,30);
        campo1->setStyleSheet("background-color:white;");

        QLabel* info3=new QLabel("* la prima lettera dev'essere maiuscola.",areaForm);
        info3->setGeometry(40,100,300,30);
        QFont font("Ubuntu",9,QFont::Normal);
        info3->setFont(font);
    }
    areaForm->show();

}


void RicercaUt::cerca() {
    if(!rUs->isChecked() && !rNmCg->isChecked()) {
        QMessageBox msg;
        msg.setText("E' necessario selezionare una modalità di ricerca!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();

    }
    else {
        QString us_nm= campo->text();
        output=new QLabel(areaRisultato);
        output->setAlignment(Qt::AlignTop);
        output->setMargin(5);

        if(!us_nm.isEmpty()) {
            if(rUs->isChecked()) {
                string dati = us_nm.toStdString();
                Utente* risultato=admin->ricercaUsername(dati);
                if(risultato) {
                    string profilo=risultato->mostraDatiAccesso()+risultato->mostraPrCompleto()+"\n";
                    QString pr=QString::fromStdString(profilo);
                    output->setText(pr);
                    output->setWordWrap(true);
                }
                else {
                    QMessageBox msg;
                    msg.setText("Ricerca fallita:l'utente cercato non è registrato in LinQedIn!");
                    msg.setIcon(QMessageBox::Warning);
                    msg.exec();
                    this->close();
                }
            }
            else { //rNmCg->isChecked()==true
                QString cogn= campo1->text();
                string nm = us_nm.toStdString();
                string cgnm=cogn.toStdString();
                list<Utente*> risultato=admin->ricercaNomeCognome(nm,cgnm);
                int numero=risultato.size();
                if(numero!=0){
                    string profili;
                    list<Utente*>::iterator it=risultato.begin();
                    for(;it!=risultato.end();++it) {
                        profili=profili+(*it)->mostraDatiAccesso()+(*it)->mostraPrCompleto()+"\n \n";
                    }
                    QString pr=QString::fromStdString(profili);
                    output->setText(pr);
                    output->setWordWrap(true);
                }
                else {
                    QMessageBox msg;
                    msg.setText("Ricerca fallita:l'utente cercato non è registrato in LinQedIn!");
                    msg.setIcon(QMessageBox::Warning);
                    msg.exec();
                    this->close();
                }
            }

            areaRisultato->setWidget(output);
            areaRisultato->ensureWidgetVisible(output);
            areaRisultato->setWidgetResizable(true);
            areaRisultato->show();
            this->close();
        }
        else {
            QMessageBox msg;
            msg.setText("Campo vuoto: immettere l'utente da cercare!");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
}

void RicercaUt::annulla() {
    this->close();
}
