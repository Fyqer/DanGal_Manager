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

namespace fs = std::filesystem;
SetNewMasterPassword::SetNewMasterPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNewMasterPassword)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DG.ico"));
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

    RemoveAllPasswords();
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


void SetNewMasterPassword::RemoveAllPasswords()
{
    std::vector<std::string> passwordFiles = GetFileNamesList();

    for(auto f : passwordFiles)
    {
        try
        {

          if (std::filesystem::remove(f))
             std::cout << "file " << f << " deleted.\n";
          else
             std::cout << "file " << f << " not found.\n";
        }
        catch(const std::filesystem::filesystem_error& err) {
           std::cout << "filesystem error: " << err.what() << '\n';
        }

    }
}

std::vector<std::string>  SetNewMasterPassword::GetFileNamesList()
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
