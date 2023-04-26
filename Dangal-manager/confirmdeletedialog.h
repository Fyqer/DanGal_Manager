#ifndef CONFIRMDELETEDIALOG_H
#define CONFIRMDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDeleteDialog;
}

class ConfirmDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDeleteDialog(QWidget *parent = nullptr);
    ~ConfirmDeleteDialog();
    QString password;
    void setPassowrd( QString password);
    void deletePassword();
    QByteArray encodePassowrd(QString password);
private slots:
    void on_buttonBox_accepted();

private:
    std::string filename;
      std::vector<std::string> lines;
    Ui::ConfirmDeleteDialog *ui;
};

#endif // CONFIRMDELETEDIALOG_H
