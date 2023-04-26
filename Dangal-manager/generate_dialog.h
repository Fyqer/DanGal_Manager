#ifndef GENERATE_DIALOG_H
#define GENERATE_DIALOG_H

#include <QDialog>

namespace Ui {
class Generate_dialog;
}

class Generate_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Generate_dialog(QWidget *parent = nullptr);
    ~Generate_dialog();

private slots:
    void on_reroll_button_clicked();
    bool is8_12Range();
    bool is13_19Range();
    bool is20_31Range();
    bool noSpecialCharacterChecked();
    int setPasswordLength();
    void on_addPasswordButton_clicked();

private:
    QString password;
    Ui::Generate_dialog *ui;
};

#endif // GENERATE_DIALOG_H
