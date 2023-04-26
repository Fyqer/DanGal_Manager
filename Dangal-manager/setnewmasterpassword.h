#ifndef SETNEWMASTERPASSWORD_H
#define SETNEWMASTERPASSWORD_H

#include <QDialog>

namespace Ui {
class SetNewMasterPassword;
}

class SetNewMasterPassword : public QDialog
{
    Q_OBJECT

public:
    explicit SetNewMasterPassword(QWidget *parent = nullptr);
    ~SetNewMasterPassword();

private slots:
    void on_buttonBox_accepted();
   void GenerateHash(QString string);

private:
   QString salt = "524w325DFG4sE$";
    QString newHashOfPassword;
    QString newMasterPassword;
    Ui::SetNewMasterPassword *ui;
};

#endif // SETNEWMASTERPASSWORD_H
