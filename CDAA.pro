QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    contacts.cpp \
    date.cpp \
    dbinterface.cpp \
    historydialog.cpp \
    interaction.cpp \
    interactions.cpp \
    jsonmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    editcontactdialog.cpp \
    todo.cpp \
    tododialog.cpp \
    todos.cpp \
    utils.cpp

HEADERS += \
    contact.h \
    contacts.h \
    date.h \
    dbinterface.h \
    historydialog.h \
    interaction.h \
    interactions.h \
    jsonmanager.h \
    mainwindow.h \
    editcontactdialog.h \
    todo.h \
    tododialog.h \
    todos.h \
    utils.h

FORMS += \
    editcontactdialog.ui \
    historydialog.ui \
    mainwindow.ui \
    tododialog.ui

TRANSLATIONS += \
    CDAA_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

RC_ICONS = contact.ico

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
