QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_password_dialog.cpp \
    checkmasterpassword.cpp \
    confirmdeletedialog.cpp \
    generate_dialog.cpp \
    main.cpp \
    mainwindowdialog.cpp \
    qaesencryption.cpp \
    selected_password_dialog.cpp \
    setnewmasterpassword.cpp

HEADERS += \
    add_password_dialog.h \
    aesni/aesni-enc-cbc.h \
    aesni/aesni-enc-ecb.h \
    aesni/aesni-key-exp.h \
    checkmasterpassword.h \
    confirmdeletedialog.h \
    generate_dialog.h \
    mainwindowdialog.h \
    qaesencryption.h \
    selected_password_dialog.h \
    setnewmasterpassword.h

FORMS += \
    add_password_dialog.ui \
    checkmasterpassword.ui \
    confirmdeletedialog.ui \
    generate_dialog.ui \
    mainwindowdialog.ui \
    selected_password_dialog.ui \
    setnewmasterpassword.ui

TRANSLATIONS += \
    Dangal-manager_pl_PL.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS +=
    qaesencryption.pro \

RESOURCES +=


DISTFILES +=


