QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    address.cpp \
    database.cpp \
    date.cpp \
    letter.cpp \
    lettertype.cpp \
    list.cpp \
    localdatabasewidget.cpp \
    main.cpp \
    maindatabasewidget.cpp \
    mainmenuwidget.cpp \
    mainwindow.cpp \
    node.cpp \
    parcel.cpp \
    parceltype.cpp \
    person.cpp \
    shipment.cpp \
    shipmentformwidget.cpp \
    shipmentprices.cpp \
    shipmentstatus.cpp \
    shipmentstatusmanager.cpp \
    shipmenttype.cpp \
    validator.cpp

HEADERS += \
    address.h \
    database.h \
    datainfo.h \
    date.h \
    letter.h \
    lettertype.h \
    list.h \
    localdatabasewidget.h \
    maindatabasewidget.h \
    mainmenuwidget.h \
    mainwindow.h \
    node.h \
    parcel.h \
    parceltype.h \
    person.h \
    shipment.h \
    shipmentformwidget.h \
    shipmentprices.h \
    shipmentstatus.h \
    shipmentstatusmanager.h \
    shipmenttype.h \
    shipmenttypeinfo.h \
    validator.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
