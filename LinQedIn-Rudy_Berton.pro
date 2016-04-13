#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T17:38:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LinQedIn-Rudy_Berton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AdminGui/cambioAccAdmin.cpp \
    AdminGui/inserimentoAdmin.cpp \
    AdminGui/mainAdmin.cpp \
    AdminGui/ricercaAdmin.cpp \
    AdminGui/rimozioneAdmin.cpp \
    ClientGui/gestisciReteClient.cpp \
    ClientGui/mainClient.cpp \
    ClientGui/modProfiloClient.cpp \
    ScheletroLogico/db.cpp \
    ScheletroLogico/errori.cpp \
    ScheletroLogico/LQInAdmin.cpp \
    ScheletroLogico/LQInClient.cpp \
    ScheletroLogico/profilo.cpp \
    ScheletroLogico/rete.cpp \
    ScheletroLogico/username.cpp \
    ScheletroLogico/utente.cpp \
    ScheletroLogico/utenteBasic.cpp \
    ScheletroLogico/utenteBusiness.cpp \
    ScheletroLogico/utenteExecutive.cpp

HEADERS  += mainwindow.h \
    AdminGui/cambioAccAdmin.h \
    AdminGui/inserimentoAdmin.h \
    AdminGui/mainAdmin.h \
    AdminGui/ricercaAdmin.h \
    AdminGui/rimozioneAdmin.h \
    ClientGui/gestisciReteClient.h \
    ClientGui/mainClient.h \
    ClientGui/modProfiloClient.h \
    ScheletroLogico/db.h \
    ScheletroLogico/errori.h \
    ScheletroLogico/LQInAdmin.h \
    ScheletroLogico/LQInClient.h \
    ScheletroLogico/profilo.h \
    ScheletroLogico/rete.h \
    ScheletroLogico/username.h \
    ScheletroLogico/utente.h \
    ScheletroLogico/utenteBasic.h \
    ScheletroLogico/utenteBusiness.h \
    ScheletroLogico/utenteExecutive.h

OTHER_FILES += \
    FileDB.txt


