#include "cambioAccAdmin.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QString>
#include <QMessageBox>
#include <Qt>
#include <string>
#include <list>
#include <QListWidgetItem>

CambioAccUt::CambioAccUt(LinQedInAdmin* ut, mainAdmin* from, QScrollArea* cornice):
    admin(ut), pagPadre(from), areaRisultato(cornice) {

    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(450, 330);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);

    QLabel* intestazione= new QLabel(this);
    intestazione->setText("Selezionare l'utente nell'elenco \ne la nuova tipologia di account che si desidera assegnare:");
    intestazione->setGeometry(20,15,450,40);
    intestazione->setWordWrap(true);

    elenco=new QListWidget(this);
    elenco->setGeometry(20,60,150,250);
    elenco->setStyleSheet("background-color:white;");
    elenco->setFrameShadow(QFrame::Raised);
    elenco->setFrameShape(QFrame::WinPanel);
    elenco->setLineWidth(1);


    vector<Utente*> utentiPresenti=admin->getDB()->getDatabase();
    vector<Utente*>::const_iterator iter=utentiPresenti.begin();
    while(iter!=utentiPresenti.end()){
        elenco->addItem((*iter)->getUsername().getLogin().data());
        ++iter;
    }
    connect(elenco,SIGNAL(clicked(QModelIndex)),this,SLOT(mostraTipologia()));

    QLabel* tipoAcc= new QLabel(this);
    tipoAcc->setText("Tipologie di account:");
    tipoAcc->setGeometry(200,130,150,20);
    basic=new QRadioButton("Basic",this);
    business=new QRadioButton("Business",this);
    executive=new QRadioButton("Executive",this);
    basic->setGeometry(215,160,100,20);
    business->setGeometry(215,190,100,20);
    executive->setGeometry(215,220,100,20);

    tastoCambia=new QPushButton("Cambia tipologia",this);
    tastoCambia->setGeometry(185,265,130,30);
    tastoCambia->setStyleSheet("background-color:white;");
    tastoCambia->setEnabled(false);
    QPushButton* annulla=new QPushButton("Annulla",this);
    annulla->setGeometry(330,265,100,30);
    annulla->setStyleSheet("background-color:white;");

    connect(tastoCambia,SIGNAL(released()),this,SLOT(cambia()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}


CambioAccUt::~CambioAccUt() {
    if(admin)
        delete admin;
    if(pagPadre)
        delete pagPadre;
}


void CambioAccUt::annulla() {
    this->close();
}

void CambioAccUt::mostraTipologia(){
    tastoCambia->setEnabled(true);

    QString dato=elenco->currentItem()->text();
    string acc=admin->ricercaUsername(dato.toStdString())->getTipoAcc();
    QString tipoAcc= QString::fromStdString(acc);

    if(acc=="basic"){
        basic->setEnabled(false);
        basic->setCheckable(false);
        business->setEnabled(true);
        executive->setEnabled(true);
        basic->setCheckable(false);
        business->setCheckable(true);
        executive->setCheckable(true);

    }
    else {
        if(acc=="business"){
            basic->setEnabled(true);
            business->setEnabled(false);
            executive->setEnabled(true);
            basic->setCheckable(true);
            business->setCheckable(false);
            executive->setCheckable(true);
        }
        else {//acc=="executive"
            basic->setEnabled(true);
            business->setEnabled(true);
            executive->setEnabled(false);
            basic->setCheckable(true);
            business->setCheckable(true);
            executive->setCheckable(false);
        }
    }

    QLabel* dati= new QLabel(this);
    dati->setText(" Utente: "+dato+"\n Tipologia di account: "+tipoAcc);
    dati->setGeometry(195,60,230,50);
    dati->setStyleSheet("background-color:white;");
    dati->setFrameShadow(QFrame::Plain);
    dati->setFrameShape(QFrame::Panel);
    dati->setLineWidth(1);

    dati->show();
}

void CambioAccUt::cambia() {
    if(!basic->isChecked() && !business->isChecked() && !executive->isChecked()){
        QMessageBox msg;
        msg.setText("Nessuna tipologia di account selezionata: si prega di sceglierne una!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else{
        string usUtente=(elenco->currentItem()->text()).toStdString();
        try {
            if(basic->isChecked()) {
                admin->cambioAccount(usUtente,"basic");
            }
            else{
                if(business->isChecked()){
                    admin->cambioAccount(usUtente,"business");
                }
                else { //executive->isChecked==true
                    admin->cambioAccount(usUtente,"executive");
                }
            }

            output=new QLabel(areaRisultato);
            output->setAlignment(Qt::AlignTop);
            output->setMargin(5);

            admin->caricaDBAdmin();
            Utente* risultato=admin->ricercaUsername(usUtente);
            string profilo=risultato->mostraDatiAccesso()+risultato->mostraPrCompleto()+"\n";
            QString pr=QString::fromStdString(profilo);
            output->setText("Tipologia di account cambiata con successo! \n\n"+pr);
            output->setWordWrap(true);
            areaRisultato->setWidget(output);
            areaRisultato->setWidgetResizable(true);
            areaRisultato->ensureWidgetVisible(output);
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

