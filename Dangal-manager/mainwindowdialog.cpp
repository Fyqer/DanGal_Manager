#include "mainwindowdialog.h"
#include "ui_mainwindowdialog.h"
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
#include <filesystem>
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
mainwindowdialog::mainwindowdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindowdialog)
{
    ui->setupUi(this);
    QPixmap pixmap("pay_ico.ico");
    ui->pushButton->setIcon(QIcon(pixmap));
    ui->pushButton->setIconSize(pixmap.size());
    setWindowIcon(QIcon("DG.ico"));
    readFile();
    fileWatcher();
    authorizedFlag = true;
}

mainwindowdialog::~mainwindowdialog()
{
    delete ui;
}
void mainwindowdialog::on_Generate_button_clicked()
{
    Generate_dialog Generate_dialog;
    Generate_dialog.setModal(true);
    Generate_dialog.exec();
}



void mainwindowdialog::readFile()
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

    authorizedFlag++;
    QStringList *allLines = new QStringList();
    allLines->clear();
    QStringListModel *linesModel = new QStringListModel(*allLines, NULL);
    for(const std::string &fileName : txtFiles )
    {

    QString qFileName = QString::fromStdString(fileName);
   // DeleteEmptyLines(fileName);
    QFile file(qFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        const char *line_c = line.data();
        QString line_str;
        line_str  = QString(line_c);

        allLines->append( qFileName.remove(qFileName.length()-4 ,4) +  "      " +  Decode(line_str));


     }
    }
 linesModel->setStringList(*allLines);
 ui->PasswordListView->setModel(linesModel);
 ui->PasswordListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


QString mainwindowdialog::Decode(QString lineString)
{
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray decodeText = encryption.decode(lineString.toLocal8Bit(), hashKey, hashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));

    return decodedString;
}

 void mainwindowdialog:: DeleteEmptyLines(const std::string &FilePath)
{
    std::ifstream in(FilePath);
    std::string line, text;
    while (std::getline(in, line))
        if ((line.empty() || line.find_first_not_of(' ') == std::string::npos) == false)
                text += line;
    in.close();
    std::ofstream out(FilePath);
    out << text;
}

void mainwindowdialog::fileWatcher()
{
    QTimer* timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, &QTimer::timeout, this, [=](){
        mainwindowdialog::readFile();
    });
    timer->start();
}


void mainwindowdialog::on_PasswordListView_pressed(const QModelIndex &index)
{
    QString itemText = index.data(Qt::DisplayRole).toString();
    QStringList firstList = itemText.split("   ");

    selected_password_dialog selected_password_dialog;
    selected_password_dialog.setModal(true);
    selected_password_dialog.setServiceAndPassowrd(firstList.takeFirst(), firstList.takeLast());
    selected_password_dialog.exec();
}

void mainwindowdialog::on_pushButton_clicked()
{
    QString link = "https://paypal.me/shazzgold?country.x=PL&locale.x=pl_PL";
    QDesktopServices::openUrl(QUrl(link));
}

