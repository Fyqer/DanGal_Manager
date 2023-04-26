#ifndef SELECTED_PASSWORD_DIALOG_H
#define SELECTED_PASSWORD_DIALOG_H

#include <QDialog>

namespace Ui {
class selected_password_dialog;
}

class selected_password_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit selected_password_dialog(QWidget *parent = nullptr);
    ~selected_password_dialog();
    QString serviceName;
    QString password;
    QString itemTextRecord;
    void setServiceAndPassowrd(QString service, QString pass);
private slots:
    void on_deleteButton_clicked();

private:
    Ui::selected_password_dialog *ui;
};

#endif // SELECTED_PASSWORD_DIALOG_H
