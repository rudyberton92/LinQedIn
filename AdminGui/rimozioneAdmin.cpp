#include "rimozioneAdmin.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QString>
#include <QMessageBox>
#include <Qt>
#include <string>


RimozioneUt::RimozioneUt(LinQedInAdmin* ut, mainAdmin* from, QScrollArea* cornice):
    admin(ut), pagPadre(from), areaRisultato(cornice) {

    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(390, 330);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);


    QLabel* intestazione= new QLabel(this);
    intestazione->setText("Selezionare dal seguente elenco \nl'utente che si desiedera eliminare:");
    intestazione->setGeometry(15,15,300,45);
    intestazione->setWordWrap(true);

    elenco=new QListWidget(this);
    elenco->setGeometry(20,65,200,250);
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
    connect(elenco,SIGNAL(clicked(QModelIndex)),this,SLOT(attivaPulsante()));

    elimina=new QPushButton("Elimina",this);
    elimina->setGeometry(255,100,100,30);
    elimina->setStyleSheet("background-color:white;");
    elimina->setEnabled(false);

    QPushButton* annulla=new QPushButton("Annulla",this);
    annulla->setGeometry(255,145,100,30);
    annulla->setStyleSheet("background-color:white;");

    connect(elimina,SIGNAL(released()),this,SLOT(rimuovi()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}


RimozioneUt::~RimozioneUt() {
    if(admin)
        delete admin;
    if(pagPadre)
        delete pagPadre;
}

void RimozioneUt::annulla() {
    this->close();
}

void RimozioneUt::attivaPulsante(){
    elimina->setEnabled(true);

}
void RimozioneUt::rimuovi() {
    QMessageBox::StandardButton conferma= QMessageBox::question(this," ","Sei sicuro di voler eliminare questo utente?", QMessageBox::Yes|QMessageBox::No);
    if(conferma==QMessageBox::Yes){
        string datoUt=(elenco->currentItem()->text()).toStdString();
        try {
            admin->rimuoviUt(datoUt);
            output=new QLabel(areaRisultato);
            output->setAlignment(Qt::AlignTop);
            output->setText("Utente eliminato con successo!");
            output->setMargin(5);
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
    else {
        this->close();
    }


}

