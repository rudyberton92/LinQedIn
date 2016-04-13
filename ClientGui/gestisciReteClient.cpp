#include "gestisciReteClient.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QLabel>

GestisciContatti::GestisciContatti(LinQedInClient* ut, mainClient* from):
    client(ut), pagPadre(from){
    pagPadre->hide();

    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(490, 365);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);

    QLabel* titolo= new QLabel(this);
    titolo->setText("LinQedIn");
    titolo->setGeometry(20,15,150,30);
    QFont font("Ubuntu",20, QFont::Bold);
    titolo->setFont(font);

    QLabel* titPag= new QLabel(this);
    titPag->setText("- Gestisci i tuoi contatti");
    titPag->setGeometry(145,15,200,30);
    QFont font2("Ubuntu",12, QFont::Bold);
    titPag->setFont(font2);

    QLabel* info1=new QLabel(this);
    info1->setText("Elenco dei tuoi contatti:");
    info1->setGeometry(30,60,200,30);

    elenco=new QListWidget(this);
    elenco->setGeometry(30,95,180,200);
    elenco->setStyleSheet("background-color:white;");
    elenco->setFrameShadow(QFrame::Raised);
    elenco->setFrameShape(QFrame::WinPanel);
    elenco->setLineWidth(1);

    list<string> contatti=client->getUt()->getRete()->getReteContatti();
    list<string>::const_iterator iter=contatti.begin();
    while(iter!=contatti.end()){
        if((*iter)=="nessuno") {
            ++iter;
        }
        else {
            elenco->addItem((*iter).data());
            ++iter;
        }
    }
    connect(elenco,SIGNAL(clicked(QModelIndex)),this,SLOT(attivaElimina()));

    QLabel* info2=new QLabel(this);
    info2->setText("Utenti che potresti conoscere:");
    info2->setGeometry(245,60,250,30);

    elenco2=new QListWidget(this);
    elenco2->setGeometry(245,95,180,200);
    elenco2->setStyleSheet("background-color:white;");
    elenco2->setFrameShadow(QFrame::Raised);
    elenco2->setFrameShape(QFrame::WinPanel);
    elenco2->setLineWidth(1);

    vector<Utente*> contatti2=client->getDb()->getDatabase();
    vector<Utente*>::const_iterator iter2=contatti2.begin();
    while(iter2!=contatti2.end()){
        if(client->getUt()->getRete()->contattoPresente((*iter2)->getUsername().getLogin()) || (client->getUt()->getUsername()).getLogin()==(*iter2)->getUsername().getLogin()) {
            ++iter2;
        }
        else {
            elenco2->addItem((*iter2)->getUsername().getLogin().data());
            ++iter2;
        }
    }

    connect(elenco2,SIGNAL(clicked(QModelIndex)),this,SLOT(attivaAggiungi()));

    elimina=new QPushButton("Elimina",this);
    elimina->setGeometry(75,310,100,30);
    elimina->setStyleSheet("background-color:white;");
    elimina->setEnabled(false);

    aggiungi=new QPushButton("Aggiungi",this);
    aggiungi->setGeometry(195,310,100,30);
    aggiungi->setStyleSheet("background-color:white;");
    aggiungi->setEnabled(false);

    QPushButton* annulla=new QPushButton("Indietro",this);
    annulla->setGeometry(315,310,100,30);
    annulla->setStyleSheet("background-color:white;");

    connect(elimina,SIGNAL(released()),this,SLOT(eliminaCont()));
    connect(aggiungi,SIGNAL(released()),this,SLOT(aggiungiCont()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}

void GestisciContatti::attivaElimina(){
    elimina->setEnabled(true);
    aggiungi->setEnabled(false);
}


void GestisciContatti::attivaAggiungi(){
    elimina->setEnabled(false);
    aggiungi->setEnabled(true);
}

void GestisciContatti::aggiungiCont() {
    if(elenco2->count()!=0){
        string contatto=(elenco2->currentItem()->text()).toStdString();
        int num=elenco2->currentRow();
        try{
            client->inserisciContRete(contatto);
            delete elenco2->takeItem(num);
            elenco->addItem(contatto.data());
        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
    else{
        QMessageBox msg;
        msg.setText("Non ci sono più utenti da aggiungere alla propria rete di contatti!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        this->close();
        pagPadre->show();
    }

}

void GestisciContatti::eliminaCont() {
    if(elenco->count()!=0){
        string contatto=(elenco->currentItem()->text()).toStdString();
        int num=elenco->currentRow();
        try{
            client->rimuoviContRete(contatto);
            delete elenco->takeItem(num);
            elenco2->addItem(contatto.data());

        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
    else {
        QMessageBox msg;
        msg.setText("Non ci sono più utenti da eliminare dalla propria rete di contatti!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        this->close();
        pagPadre->show();
    }
}

void GestisciContatti::annulla() {
    this->close();
    pagPadre->show();
}

GestisciContatti::~GestisciContatti() {
    if(client)
        delete client;
    if(pagPadre)
        delete pagPadre;
}
