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
#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;
ConfirmDeleteDialog::ConfirmDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDeleteDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DG.ico"));
}

ConfirmDeleteDialog::~ConfirmDeleteDialog()
{
    delete ui;
}
void ConfirmDeleteDialog::setPassowrd(QString psswd)
{
    fileName = psswd;
}
void ConfirmDeleteDialog::deletePassword()
{
//finding
 auto f = (fileName + ".txt").toStdString();
//deleting
 try {

   if (std::filesystem::remove(f))
      std::cout << "file " << f << " deleted.\n";
   else
      std::cout << "file " << f << " not found.\n";
 }
 catch(const std::filesystem::filesystem_error& err) {
    std::cout << "filesystem error: " << err.what() << '\n';
 }

}

void ConfirmDeleteDialog::on_buttonBox_accepted()
{
    ConfirmDeleteDialog::deletePassword();
}

