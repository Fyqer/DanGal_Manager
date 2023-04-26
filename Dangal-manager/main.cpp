#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QtCore>
#include <QMessageBox>
#include <iostream>
#include "setnewmasterpassword.h"
#include "checkmasterpassword.h"
#include <QCryptographicHash>
#include <QStringListModel>
#include <QFile>
#include <QApplication>
#include <QtGui>
#include <thread>
#include <qobject.h>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdio.h>
#include <cstring>
#include <future>
#include <unistd.h>
#include <algorithm>
#include <QCryptographicHash>
#include "qaesencryption.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString key="5TGB&YHN7UJM(IK<";
    QString iv="!QAZ2WSX#EDC4RFV";
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Dangal-manager_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QFile file("masterPassword.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        SetNewMasterPassword registerNew;
        registerNew.show();
        return registerNew.exec();
    }
    else
    {

    file.close();
    CheckMasterPassword login;
    login.show();
    const int x =  login.exec();
    return x;
    }
}

