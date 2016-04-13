#include "inserimentoAdmin.h"

#include <QPushButton>
#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QString>
#include <QMessageBox>
#include <Qt>
#include <QLabel>
#include <string>
#include <list>
#include <QFrame>

InserimentoUt::InserimentoUt(LinQedInAdmin* ut, mainAdmin* from, QScrollArea* cornice):
    admin(ut), pagPadre(from), areaRisultato(cornice) {

    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(600, 400);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);


    QLabel* intestazione= new QLabel(this);
    intestazione->setText("Per l'inserimento di un nuovo utente riempire i seguenti campi:");
    intestazione->setGeometry(30,15,550,30);

    QLabel* username= new QLabel(this);
    username->setText("Username:");
    username->setGeometry(30,60,100,30);
    username->setAlignment(Qt::AlignCenter);
    us=new QLineEdit(this);
    us->setGeometry(120,60,130,30);
    us->setStyleSheet("background-color:white;");

    QLabel* password= new QLabel(this);
    password->setText("Password:");
    password->setGeometry(270,60,100,30);
    password->setAlignment(Qt::AlignCenter);
    pw=new QLineEdit(this);
    pw->setGeometry(360,60,130,30);
    pw->setStyleSheet("background-color:white;");

    QLabel* nome= new QLabel(this);
    nome->setText("Nome*:");
    nome->setGeometry(40,130,70,30);
    nome->setAlignment(Qt::AlignCenter);
    nm=new QLineEdit(this);
    nm->setGeometry(120,130,130,30);
    nm->setStyleSheet("background-color:white;");

    QLabel* cognome= new QLabel(this);
    cognome->setText("Cognome*:");
    cognome->setGeometry(280,130,80,30);
    cognome->setAlignment(Qt::AlignCenter);
    cg=new QLineEdit(this);
    cg->setGeometry(370,130,130,30);
    cg->setStyleSheet("background-color:white;");

    QLabel* data= new QLabel(this);
    data->setText("Data di Nascita (gg/mm/aaaa):");
    data->setGeometry(40,180,230,30);
    data->setAlignment(Qt::AlignCenter);
    dtN=new QLineEdit(this);
    dtN->setGeometry(280,180,130,30);
    dtN->setStyleSheet("background-color:white;");

    QLabel* email= new QLabel(this);
    email->setText("Email:");
    email->setGeometry(40,230,70,30);
    email->setAlignment(Qt::AlignCenter);
    em=new QLineEdit(this);
    em->setGeometry(120,230,220,30);
    em->setStyleSheet("background-color:white;");

    QLabel* tipoAcc= new QLabel(this);
    tipoAcc->setText("Tipologia di Account:");
    tipoAcc->setGeometry(30,280,150,30);

    QFrame* pulsantiAcc=new QFrame(this);
    pulsantiAcc->setGeometry(20,315,400,50);
    pulsantiAcc->setFrameShadow(QFrame::Plain);
    pulsantiAcc->setFrameShape(QFrame::Box);
    pulsantiAcc->setLineWidth(1);

    basic=new QRadioButton("Basic",pulsantiAcc);
    business=new QRadioButton("Business",pulsantiAcc);
    executive=new QRadioButton("Executive",pulsantiAcc);
    basic->setGeometry(20,15,80,25);
    business->setGeometry(120,15,100,25);
    executive->setGeometry(260,15,100,25);
    basic->setChecked(true);

    QPushButton* inserisci=new QPushButton("Inserisci",this);
    inserisci->setGeometry(450,280,100,30);
    inserisci->setStyleSheet("background-color:white;");
    QPushButton* annulla=new QPushButton("Annulla",this);
    annulla->setGeometry(450,330,100,30);
    annulla->setStyleSheet("background-color:white;");

    QLabel* info=new QLabel("* la prima lettera dev'essere maiuscola.",this);
    info->setGeometry(30,365,300,30);
    QFont font("Ubuntu",9,QFont::Normal);
    info->setFont(font);

    connect(inserisci,SIGNAL(released()),this,SLOT(inserisci()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}


InserimentoUt::~InserimentoUt() {
    if(admin)
        delete admin;
    if(pagPadre)
        delete pagPadre;
}

void InserimentoUt::inserisci() {
    QString nmF, cgF, dtF, emF, usF, pwF;
    nmF=nm->text();
    cgF=cg->text();
    dtF=dtN->text();
    emF=em->text();
    usF=us->text();
    pwF=pw->text();

    if(usF.isEmpty() || pwF.isEmpty() || nmF.isEmpty() || cgF.isEmpty() || dtF.isEmpty() || emF.isEmpty()) {
        QMessageBox msg;
        msg.setText("Sono presenti dei campi vuoti: tutti i campi devono essere riempiti!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else {
        string username, password, nome, cognome, data, email;
        username=usF.toStdString();
        password=pwF.toStdString();
        nome = nmF.toStdString();
        cognome=cgF.toStdString();
        data=dtF.toStdString();
        email=emF.toStdString();

        Username usUt(username,password);
        Profilo pfUt(nome,cognome,data,email);
        Utente* nuovoUt=0;

        if(basic->isChecked()) {
            nuovoUt=new UtBasic(usUt,pfUt);
        }
        else {
            if(business->isChecked()) {
                nuovoUt=new UtBusiness(usUt,pfUt);
            }
            else {//executive->isChecked==true
                nuovoUt=new UtExecutive(usUt,pfUt);
            }
        }

        try {
            admin->inserisciUt(nuovoUt);
            QLabel* output=new QLabel(areaRisultato);
            output->setAlignment(Qt::AlignTop);
            output->setMargin(5);

            admin->caricaDBAdmin();
            Utente* risultato=admin->ricercaUsername(username);

            string profilo=risultato->mostraDatiAccesso()+risultato->mostraPrCompleto()+"\n";

            QString pr=QString::fromStdString(profilo);
            output->setText("Utente inserito con successo! \n\n"+pr);
            output->setWordWrap(true);
            areaRisultato->setWidget(output);
            areaRisultato->ensureWidgetVisible(output);
            areaRisultato->setWidgetResizable(true);
            areaRisultato->show();
            this->close();
        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
}

void InserimentoUt::annulla() {
    this->close();
}
