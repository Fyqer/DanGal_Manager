#ifndef ADD_PASSWORD_DIALOG_H
#define ADD_PASSWORD_DIALOG_H

#include <QDialog>

namespace Ui {
class add_password_dialog;
}

class add_password_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_password_dialog(QWidget *parent = nullptr);
    ~add_password_dialog();
    QString serviceName;
    QString password;
    void setPassword(QString s);
    void addPassword(QByteArray passEncoded);

private slots:
    void on_pushButton_clicked();

private:
    Ui::add_password_dialog *ui;
    QByteArray encodePassowrd(QString password);
};

#endif // ADD_PASSWORD_DIALOG_H
