#include "confirmdeletedialog.h"
#include "ui_confirmdeletedialog.h"
#include <QFile>
#include <cstdio> // include for std::rename
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
ConfirmDeleteDialog::ConfirmDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDeleteDialog)
{
    ui->setupUi(this);
}

ConfirmDeleteDialog::~ConfirmDeleteDialog()
{
    delete ui;
}
void ConfirmDeleteDialog::setPassowrd(QString psswd)
{
    password = psswd;
}
void ConfirmDeleteDialog::deletePassword()
{
//finding
 password.toStdString();
    std::ifstream data_store;
    std::string linee;
    auto  pswd =  QString::fromLocal8Bit("\n" + encodePassowrd(password)).toStdString();

    std::string lineFound;
    data_store.open("secure_secrets.txt");
    while (getline(data_store, linee))
    {
        if (linee.find(pswd) != std::string::npos)
            lineFound = linee;
    }
    std::cout<< pswd;
data_store.close();

    //deleting
    std::string line;
    std::ifstream file;
      std::ofstream outfile;
      file.open("secure_secrets.txt");
      outfile.open("newM.txt");
      while (getline(file, line)) {
          if (line != lineFound) {
              outfile << line << std::endl;
          }
      }
      outfile.close();
      file.close();
      remove("secure_secrets.txt");
      rename("newM.txt", "secure_secrets.txt");

}

QByteArray ConfirmDeleteDialog::encodePassowrd(QString record)
{

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString key("5TGB&YHN7UJM(IK<");
    QString iv("!QAZ2WSX#EDC4RFV");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodeText = encryption.encode(record.toLocal8Bit(), hashKey, hashIV);
    return encodeText;

}
void ConfirmDeleteDialog::on_buttonBox_accepted()
{
    ConfirmDeleteDialog::deletePassword();
}

