#include "add_password_dialog.h"
#include "ui_add_password_dialog.h"
#include <QFile>
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
add_password_dialog::add_password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_password_dialog)
{
    ui->setupUi(this);
}

add_password_dialog::~add_password_dialog()
{
    delete ui;
}


void add_password_dialog::setPassword(QString psswd)
{
   password = psswd;
   ui->passwordLabelEdit->setText(psswd);
}


void add_password_dialog::addPassword(QByteArray password)
{
    // Create a new file
       QFile file("secure_secrets.txt");
       file.open(QIODevice::WriteOnly | QIODevice::Append);
       QTextStream out(&file);
       QString passwordString = QString::fromLocal8Bit(password);
       out <<  passwordString;
       out << "\n";
       file.close();
 }

QByteArray add_password_dialog::encodePassowrd(QString password)
{

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key("5TGB&YHN7UJM(IK<");
    QString iv("!QAZ2WSX#EDC4RFV");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(password.toLocal8Bit(), hashKey, hashIV);
    return encodeText;

}
void add_password_dialog::on_pushButton_clicked()
{
      addPassword(encodePassowrd( /*ui->serviceNameEdit->toPlainText() + "   " +  na razie bez*/ ui->passwordLabelEdit->toPlainText()));
}

