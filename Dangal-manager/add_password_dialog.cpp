#include "add_password_dialog.h"
#include "qmessagebox.h"
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
namespace fs = std::filesystem;
add_password_dialog::add_password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_password_dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DG.ico"));
}

add_password_dialog::~add_password_dialog()
{
    delete ui;
}



std::vector<std::string> getFileNamesList()
{
    std::vector<std::string> txtFiles;
    std::string path = ".";
    for (const auto &entry : fs::directory_iterator(path)) {
         // Check if the file has a .txt extension and exclude "masterPassword.txt"
         if (entry.path().extension() == ".txt" && entry.path().filename() != "masterPassword.txt") {
             std::cout << entry.path() << std::endl;
             txtFiles.push_back(entry.path().filename().string());
         }
     }
    return txtFiles;
}



void add_password_dialog::setPassword(QString psswd)
{
   password = psswd;
   ui->passwordLabelEdit->setText(psswd);
}

// nie moze byc taka sama nazwa pliku - sprawdzic!

void add_password_dialog::addPassword(QString filename, QByteArray password)
{
     std::vector<std::string> fileNames = getFileNamesList();

     auto it = std::find(fileNames.begin(), fileNames.end(), (filename + ".txt").toStdString());
         if (it == fileNames.end()) {
    // Create a new file
       QFile file(filename + ".txt");
       file.open(QIODevice::WriteOnly | QIODevice::Append);
       QTextStream out(&file);
       QString passwordString = QString::fromLocal8Bit(password);
       out <<  passwordString;
       file.close();
         }
         else
         {
             QMessageBox msgBox;
             msgBox.setText("Service already exists. Delete previous password and set new one.");
             msgBox.exec();
             return;
         }
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
      addPassword( ui->serviceNameEdit->toPlainText(), encodePassowrd(ui->passwordLabelEdit->toPlainText()));
}

