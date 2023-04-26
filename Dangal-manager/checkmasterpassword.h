#ifndef CHECKMASTERPASSWORD_H
#define CHECKMASTERPASSWORD_H

#include <QDialog>

namespace Ui {
class CheckMasterPassword;
}

class CheckMasterPassword : public QDialog
{
    Q_OBJECT

public:
    explicit CheckMasterPassword(QWidget *parent = nullptr);
    ~CheckMasterPassword();
QString GenerateHash(QString masterPassword);
private slots:
void on_buttonBox_accepted();

private:
QString salt = "524w325DFG4sE$";
std::string filePath = "masterPasword";
QString providedPassord;
QString masterPasswordHash;
QString GetFileHash();
Ui::CheckMasterPassword *ui;

};

#endif // CHECKMASTERPASSWORD_H
