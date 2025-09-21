TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        compresion.cpp \
        encriptacion.cpp \
        main.cpp

HEADERS += \
    compresion.h \
    encriptacion.h

DISTFILES += \
    datasetDesarrollo/Encriptado1.txt \
    datasetDesarrollo/Encriptado2.txt \
    datasetDesarrollo/Encriptado3.txt \
    datasetDesarrollo/Encriptado4.txt \
    datasetDesarrollo/pista1.txt \
    datasetDesarrollo/pista2.txt \
    datasetDesarrollo/pista3.txt \
    datasetDesarrollo/pista4.txt
