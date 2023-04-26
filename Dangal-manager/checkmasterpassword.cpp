#include "checkmasterpassword.h"
#include "mainwindowdialog.h"
#include "ui_checkmasterpassword.h"
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QtCore>
#include <QMessageBox>
#include <iostream>
CheckMasterPassword::CheckMasterPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckMasterPassword)
{
    ui->setupUi(this);
}

CheckMasterPassword::~CheckMasterPassword()
{
    delete ui;
}
QString CheckMasterPassword::GenerateHash(QString masterPassword)
{
    return QString(QCryptographicHash::hash((masterPassword.toStdString()),QCryptographicHash::Md5).toHex());
}

void CheckMasterPassword::on_buttonBox_accepted()
{
 providedPassord =  ui->masterPassword->toPlainText();
  QFile file("masterPassword.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      QMessageBox msgBox;
      msgBox.setText("File with passowrd do not exists or its not readable!");
      msgBox.exec();
      return;
  }
    QTextStream in(&file);
    QString hash = GenerateHash(salt+providedPassord+salt);
    while (!in.atEnd())
    {
      masterPasswordHash = in.readLine();
    }
      file.close();

    if(masterPasswordHash == hash)
    {
        mainwindowdialog mainwindowdialog;
        mainwindowdialog.setModal(true);
        mainwindowdialog.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Your password is wrong!");
        msgBox.exec();
    }
}

