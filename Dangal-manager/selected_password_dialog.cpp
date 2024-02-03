#include "selected_password_dialog.h"
#include "confirmdeletedialog.h"
#include "ui_selected_password_dialog.h"
selected_password_dialog::selected_password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selected_password_dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DG.ico"));
}

selected_password_dialog::~selected_password_dialog()
{
    delete ui;
}

void selected_password_dialog::setServiceAndPassowrd(QString service, QString password)
{
    serviceName = service;
    ui->passwordLabelEdit->setText(password);
    ui->serviceNameEdit->setText(serviceName);
    ui->serviceNameEdit->setReadOnly(true);
    ui->passwordLabelEdit->setReadOnly(true);
    itemTextRecord =  ui->serviceNameEdit->toPlainText(); //+ "   " +  ui->passwordLabelEdit->toPlainText();
}

void selected_password_dialog::on_deleteButton_clicked()
{
   ConfirmDeleteDialog ConfirmDeleteDialog;
   ConfirmDeleteDialog.setPassowrd(itemTextRecord);
   ConfirmDeleteDialog.setModal(true);
   ConfirmDeleteDialog.exec();
}

