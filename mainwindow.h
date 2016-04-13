#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ScheletroLogico/errori.h"
#include "ScheletroLogico/LQInAdmin.h"
#include "ClientGui/mainClient.h"
#include "AdminGui/mainAdmin.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton* client, *admin;
    QLineEdit* username, *password;

private slots:
    void chiudi() const;
    void carica();

};

#endif
