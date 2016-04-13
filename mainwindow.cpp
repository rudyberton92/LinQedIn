#include "mainwindow.h"

#include <QLabel>
#include <Qt>
#include <QApplication>
#include <QFont>
#include <QRect>
#include <QDesktopWidget>
#include <QString>
#include <string>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->setStyleSheet("background-color:lightblue;");
    this->setFixedSize(600, 430);
    QRect screenGeometry=QApplication::desktop()->screenGeometry();
    int x=(screenGeometry.width()-width())/2;
    int y=(screenGeometry.height()-height())/2;
    move(x,y);

    QLabel* titolo= new QLabel(this);
    titolo->setText("Benvenuto in LinQedIn");
    titolo->setAlignment(Qt::AlignCenter);
    titolo->setGeometry(0,25,600,30);
    QFont font("Ubuntu",20, QFont::Bold);
    titolo->setFont(font);

    QLabel* indicazione=new QLabel(this);
    indicazione->setText("Seleziona la modalità di accesso ed inserisci i tuoi dati:");
    indicazione->setGeometry(0, 85, 600, 15);
    indicazione->setAlignment(Qt::AlignCenter);

    client=new QPushButton("Utente",this);
    client->setGeometry(160,120,130,35);
    client->setStyleSheet("background-color:white;");
    admin=new QPushButton("Amministratore",this);
    admin->setGeometry(305,120,130,35);
    admin->setStyleSheet("background-color:white;");

    client->setCheckable(true);
    admin->setCheckable(true);

    QLabel* usnm = new QLabel("Username: ", this);
    usnm->setGeometry(180,200,100,30);
    QLabel* pw = new QLabel("Password: ", this);
    pw->setGeometry(180,250,100,30);
    username =new QLineEdit(this);
    username->setGeometry(265,200,150,30);
    username->setStyleSheet("background-color:white;");
    password = new QLineEdit(this);
    password->setGeometry(265,250,150,30);
    password->setStyleSheet("background-color:white;");
    password->setEchoMode(QLineEdit::Password);

    QPushButton* entra=new QPushButton("Entra",this);
    entra->setGeometry(190,320,100,30);
    entra->setStyleSheet("background-color:white;");
    connect(entra,SIGNAL(released()),this,SLOT(carica()));

    QPushButton* chiudi=new QPushButton("Chiudi",this);
    chiudi->setGeometry(305,320,100,30);
    chiudi->setStyleSheet("background-color:white;");
    connect(chiudi,SIGNAL(released()),this,SLOT(chiudi()));

}


MainWindow::~MainWindow()
{   delete client;
    delete admin;
    delete username;
    delete password;
}

void MainWindow::chiudi() const{
    qApp->exit();
}


void MainWindow::carica() {
    QString usname= username->text();
    string usnm = usname.toStdString();

    QString psword = password->text();
    string pw = psword.toStdString();

    if(usnm.empty() || pw.empty()) {
        password->clear();
        QMessageBox msg;
        msg.setText("Campo username e/o password vuoti!");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }

    else {
        if(client->isChecked() && !admin->isChecked()) { //si sta autenticando un utente
            try {
                mainClient* utente=new mainClient(usnm,pw,this);
                username->clear();
                password->clear();
                client->setChecked(false);
                this->hide();
                utente->show();
            }

            catch(Errore err){
                password->clear();
                QMessageBox msg;
                msg.setText(err.mostraErrore().data());
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        }
        else {
            if(!client->isChecked() && admin->isChecked()) { //si sta autenticando l'amministratore
                try {
                    mainAdmin* amministratore=new mainAdmin(usnm,pw,this);
                    username->clear();
                    password->clear();
                    admin->setChecked(false);
                    this->hide();
                    amministratore->show();
                }

                catch(Errore err){
                    password->clear();
                    QMessageBox msg;
                    msg.setText(err.mostraErrore().data());
                    msg.setIcon(QMessageBox::Warning);
                    msg.exec();
                }
            }
            else {
                QMessageBox msg;
                msg.setText("Selezionare una modalità di accesso: Utente o Amministratore!");
                msg.setIcon(QMessageBox::Information);
                msg.exec();
            }
        }
    }
}



