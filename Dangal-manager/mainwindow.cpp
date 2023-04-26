#include "mainwindow.h"
#include "generate_dialog.h"
#include "selected_password_dialog.h"
#include "ui_mainwindow.h"
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
#include <unistd.h>
#include <algorithm>
#include <QCryptographicHash>
#include "qaesencryption.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{

   // ui->setupUi(this);
    readFile();
    fileWatcher();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Generate_button_clicked()
{
    Generate_dialog Generate_dialog;
    Generate_dialog.setModal(true);
    Generate_dialog.exec();
}



void MainWindow::readFile()
{

    QStringList *allLines = new QStringList();
    allLines->clear();
    QStringListModel *linesModel = new QStringListModel(*allLines, NULL);

    QFile file("secure_secrets.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        const char *line_c = line.data();
        QString line_str = QString(QLatin1String(line_c));
        allLines->append(line_str);
    }
    linesModel->setStringList(*allLines);
    ui->PasswordListView->setModel(linesModel);
    ui->PasswordListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList list;
//https://github.com/bricke/Qt-AES


   /* QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
                     "is a specification for the encryption of electronic data established by the U.S. "
                    "National Institute of Standards and Technology (NIST) in 2001");
    QString key("5TGB&YHN7UJM(IK<");
    QString iv("!QAZ2WSX#EDC4RFV");
    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
    QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));
         cout << " decodedString:" +   decodedString.toStdString()+  "\n";
         */
}

void DeleteEmptyLines(const std::string &FilePath)
{
    std::ifstream in(FilePath);
    std::string line, text;
    while (std::getline(in, line))
        if ((line.empty() || line.find_first_not_of(' ') == std::string::npos) == false)
                text += line + "\n";
    in.close();
    std::ofstream out(FilePath);
    out << text;
}


void MainWindow::fileWatcher()
{
    QTimer* timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, [=](){
        MainWindow::readFile();
    });
    timer->start();
}


void MainWindow::on_PasswordListView_pressed(const QModelIndex &index)
{
    QString itemText = index.data(Qt::DisplayRole).toString();
    QStringList firstList = itemText.split("   ");

    selected_password_dialog selected_password_dialog;
    selected_password_dialog.setModal(true);
    selected_password_dialog.setServiceAndPassowrd(firstList.takeFirst(), firstList.takeLast());
    selected_password_dialog.exec();

}



//decodedString == inputStr !!




