#include "setnewmasterpassword.h"
#include "ui_setnewmasterpassword.h"
#include "mainwindow.h"
#include "ui_checkmasterpassword.h"
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QtCore>
#include <QMessageBox>
#include <iostream>
SetNewMasterPassword::SetNewMasterPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNewMasterPassword)
{
    ui->setupUi(this);
}

SetNewMasterPassword::~SetNewMasterPassword()
{
    delete ui;
}

void SetNewMasterPassword::GenerateHash(QString masterPassword)
{
    newHashOfPassword =  QString(QCryptographicHash::hash((masterPassword.toStdString()),QCryptographicHash::Md5).toHex());

}

void SetNewMasterPassword::on_buttonBox_accepted()
{

    newMasterPassword =  ui->masterPassword->toPlainText();

    GenerateHash(salt+newMasterPassword+salt);
    QString filename = "masterPassword.txt";
    try {
       if (std::filesystem::remove(filename.toStdString()))
          std::cout << "file " << filename.toStdString() << " deleted.\n";
       else
          std::cout << "file " << filename.toStdString() << " not found.\n";
     }
     catch(const std::filesystem::filesystem_error& err) {
     }
      QFile file(filename);
      if (file.open(QIODevice::ReadWrite)) {
          QTextStream stream(&file);
          stream << newHashOfPassword << Qt::endl;
      }
      file.close();
}

