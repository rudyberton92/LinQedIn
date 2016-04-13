#include "modProfiloClient.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QLabel>


ModificaProfilo::ModificaProfilo(LinQedInClient* ut, mainClient* from):
    client(ut), pagPadre(from) {
    pagPadre->hide();
    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(580, 470);
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
    titPag->setText("- Modifica i tuoi dati");
    titPag->setGeometry(145,15,200,30);
    QFont font2("Ubuntu",12, QFont::Bold);
    titPag->setFont(font2);

    emPw=new QPushButton("Password/Email",this);
    emPw->setGeometry(30,55,150,30);
    emPw->setStyleSheet("background-color:white;");

    tit=new QPushButton("Titoli di studio",this);
    tit->setGeometry(200,55,160,30);
    tit->setStyleSheet("background-color:white;");

    lin=new QPushButton("Lingue conosciute",this);
    lin->setGeometry(380,55,160,30);
    lin->setStyleSheet("background-color:white;");

    comp=new QPushButton("Competenze lavorative",this);
    comp->setGeometry(80,100,200,30);
    comp->setStyleSheet("background-color:white;");

    esp=new QPushButton("Esperienze professionali",this);
    esp->setGeometry(310,100,200,30);
    esp->setStyleSheet("background-color:white;");

    QPushButton* tornaIndietro=new QPushButton("<< Torna indietro",this);
    tornaIndietro->setGeometry(390,375,140,30);
    tornaIndietro->setStyleSheet("background-color:white;");

    emPw->setCheckable(true);
    tit->setCheckable(true);
    lin->setCheckable(true);
    comp->setCheckable(true);
    esp->setCheckable(true);

    connect(emPw,SIGNAL(clicked()),this,SLOT(modEmPw()));
    connect(tit,SIGNAL(clicked()),this,SLOT(modifica()));
    connect(lin,SIGNAL(clicked()),this,SLOT(modifica()));
    connect(comp,SIGNAL(clicked()),this,SLOT(modifica()));
    connect(esp,SIGNAL(clicked()),this,SLOT(modifica()));
    connect(tornaIndietro,SIGNAL(released()),this,SLOT(tornaIndietro()));
}

ModificaProfilo::~ModificaProfilo(){
    if(client)
        delete client;
    if(pagPadre)
        delete pagPadre;
}

void ModificaProfilo::tornaIndietro() {
    this->close();
    pagPadre->show();
}

void ModificaProfilo::modEmPw() {
    emPw->setDisabled(true);
    tit->setDisabled(true);
    comp->setDisabled(true);
    lin->setDisabled(true);
    esp->setDisabled(true);

    cornice=new QFrame(this);
    cornice->setGeometry(0,145,580,320);
    QLabel* info1=new QLabel("Cambia la tua email:",cornice);
    info1->setGeometry(20,10,200,20);

    em=new QLineEdit(cornice);
    em->setGeometry(40,35,250,30);
    em->setStyleSheet("background-color:white;");

    QPushButton* cambia1=new QPushButton("Cambia",cornice);
    cambia1->setGeometry(305,35,100,30);
    cambia1->setStyleSheet("background-color:white;");

    QLabel* info2=new QLabel("Cambia la tua password:",cornice);
    info2->setGeometry(20,85,180,20);

    QLabel* info3=new QLabel("Nuova password:",cornice);
    info3->setGeometry(40,115,130,20);

    pw=new QLineEdit(cornice);
    pw->setGeometry(205,115,200,30);
    pw->setStyleSheet("background-color:white;");
    pw->setEchoMode(QLineEdit::Password);

    QLabel* info4=new QLabel("Conferma password:",cornice);
    info4->setGeometry(40,155,150,20);

    confPw=new QLineEdit(cornice);
    confPw->setGeometry(205,155,200,30);
    confPw->setStyleSheet("background-color:white;");
    confPw->setEchoMode(QLineEdit::Password);

    QPushButton* cambia2=new QPushButton("Cambia",cornice);
    cambia2->setGeometry(415,155,100,30);
    cambia2->setStyleSheet("background-color:white;");

    QPushButton* annulla=new QPushButton("Indietro",cornice);
    annulla->setGeometry(430,230,100,30);
    annulla->setStyleSheet("background-color:white;");

    cornice->show();

    connect(cambia1,SIGNAL(released()),this,SLOT(modificaEm()));
    connect(cambia2,SIGNAL(released()),this,SLOT(modificaPw()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));
}

void ModificaProfilo::modificaEm() {
    string email=(em->text()).toStdString();
    if(email.empty()) {
        QMessageBox msg;
        msg.setText("Il campo per il cambio dell'email è vuoto!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else {
        try {
            client->cambiaEmail(email);
            em->clear();
            QLabel* emailOk=new QLabel("Email cambiata con successo!",cornice);
            emailOk->setGeometry(40,225,250,40);
            emailOk->setStyleSheet("background-color:white;");
            emailOk->setAlignment(Qt::AlignCenter);
            emailOk->setFrameShadow(QFrame::Plain);
            emailOk->setFrameShape(QFrame::Panel);
            emailOk->setLineWidth(1);
            emailOk->show();
        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
}

void ModificaProfilo::modificaPw() {
    string password=(pw->text()).toStdString();
    string confPassword=(confPw->text()).toStdString();

    if(!password.empty() && !confPassword.empty()) {
        if(password==confPassword) {
            try{
                client->cambiaPassword(password);
                pw->clear();
                confPw->clear();
                QLabel* passwordOk=new QLabel("Password cambiata con successo!",cornice);
                passwordOk->setGeometry(40,225,250,40);
                passwordOk->setStyleSheet("background-color:white;");
                passwordOk->setAlignment(Qt::AlignCenter);
                passwordOk->setFrameShadow(QFrame::Plain);
                passwordOk->setFrameShape(QFrame::Panel);
                passwordOk->setLineWidth(1);
                passwordOk->show();
            }
            catch(Errore err){
                QMessageBox msg;
                msg.setText(err.mostraErrore().data());
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        }
        else {
            pw->clear();
            confPw->clear();
            QMessageBox msg;
            msg.setText("I campi Nuova Password e Conferma Password non coincidono, reinserire i valori!");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }

    }
    else {
        QMessageBox msg;
        msg.setText("I campi per il cambio della password sono vuoti!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}

void ModificaProfilo::modifica(){
    emPw->setDisabled(true);
    tit->setDisabled(true);
    comp->setDisabled(true);
    lin->setDisabled(true);
    esp->setDisabled(true);

    cornice=new QFrame(this);
    cornice->setGeometry(0,145,580,320);

    QLabel* info1=new QLabel(cornice);
    info1->setGeometry(20,0,300,20);

    QLabel* info2=new QLabel(cornice);
    info2->setGeometry(20,155,320,20);

    elenco=new QListWidget(cornice);
    elenco->setGeometry(20,25,540,120);
    elenco->setStyleSheet("background-color:white;");
    elenco->setFrameShadow(QFrame::Raised);
    elenco->setFrameShape(QFrame::WinPanel);
    elenco->setLineWidth(1);

    vector<string> elemento;
    if(tit->isChecked()){
        info1->setText("I tuoi titoli di studio:");
        info2->setText("Inserisci un nuovo titolo di studio:");
        elemento=(client->getUt()->getProfilo()).getTitoli();

    }
    else {
        if(lin->isChecked()) {
            info1->setText("Le lingue che conosci:");
            info2->setText("Inserisci una nuova lingua:");
            elemento=(client->getUt()->getProfilo()).getLingue();


        }
        else {
            if(comp->isChecked()){
                info1->setText("Le tue competenze lavorative:");
                info2->setText("Inserisci una nuova competenza lavorativa:");
                elemento=(client->getUt()->getProfilo()).getCompetenze();
            }
            else{//esp->isChecked()
                info1->setText( "Le tue esperienze professionali:");
                info2->setText("Inserisci una nuova esperienza professionale:");
                elemento=(client->getUt()->getProfilo()).getEsperienze();
            }

        }
    }

    vector<string>::const_iterator iter=elemento.begin();
    while(iter!=elemento.end()){
        if((*iter)=="informazione mancante") {
            ++iter;
        }
        else {
            elenco->addItem((*iter).data());
            ++iter;
        }
    }
    connect(elenco,SIGNAL(clicked(QModelIndex)),this,SLOT(attivaPulsante()));

    campo=new QTextEdit(cornice);
    campo->setGeometry(20,180,350,100);
    campo->setStyleSheet("background-color:white;");
    campo->lineWrapMode();
    campo->setFrameShadow(QFrame::Plain);
    campo->setFrameShape(QFrame::Panel);
    campo->setLineWidth(1);


    QPushButton* aggiungi=new QPushButton("Aggiungi",cornice);
    aggiungi->setGeometry(270,285,100,30);
    aggiungi->setStyleSheet("background-color:white;");

    elimina=new QPushButton("Elimina",cornice);
    elimina->setGeometry(430,180,100,30);
    elimina->setStyleSheet("background-color:white;");
    elimina->setEnabled(false);

    QPushButton* annulla=new QPushButton("Indietro",cornice);
    annulla->setGeometry(430,230,100,30);
    annulla->setStyleSheet("background-color:white;");

    cornice->show();

    connect(aggiungi,SIGNAL(released()),this,SLOT(aggiungiDato()));
    connect(elimina,SIGNAL(released()),this,SLOT(eliminaDato()));
    connect(annulla,SIGNAL(released()),this,SLOT(annulla()));

}

void ModificaProfilo::aggiungiDato(){
    string dato=(campo->toPlainText()).toStdString();
    if(dato.empty()) {
        QMessageBox msg;
        msg.setText("Campo per l'inserimento vuoto!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else {
        try{
            if(tit->isChecked()){
                client->aggiungiTitoli(dato);
            }
            else {
                if(lin->isChecked()) {
                    client->aggiungiLingue(dato);
                }
                else {
                    if(comp->isChecked()) {
                        client->aggiungiCompetenze(dato);
                    }
                    else { //esp->isChecked()==true
                        client->aggiungiEsperienze(dato);
                    }
                }
            }
            campo->clear();
            elenco->addItem(dato.data());
        }
        catch(Errore err){
            QMessageBox msg;
            msg.setText(err.mostraErrore().data());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    }
}

void ModificaProfilo::eliminaDato() {
    if(elenco->count()!=0){
        int num=elenco->currentRow();
        try{
            if(tit->isChecked()){
                client->eliminaTitoli(num);
            }
            else {
                if(lin->isChecked()) {
                    client->eliminaLingue(num);
                }
                else {
                    if(comp->isChecked()) {
                        client->eliminaCompetenze(num);
                    }
                    else { //esp->isChecked()==true
                        client->eliminaEsperienze(num);
                    }
                }
            }
            delete elenco->takeItem(num);
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
        msg.setText("Non ci sono più voci da eliminare!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        annulla();
    }
}


void ModificaProfilo::attivaPulsante(){
    elimina->setEnabled(true);

}

void ModificaProfilo::annulla() {
    client->salvaDBClient();

    emPw->setDisabled(false);
    emPw->setChecked(false);
    tit->setDisabled(false);
    tit->setChecked(false);
    lin->setDisabled(false);
    lin->setChecked(false);
    comp->setDisabled(false);
    comp->setChecked(false);
    esp->setDisabled(false);
    esp->setChecked(false);

    cornice->close();
}

