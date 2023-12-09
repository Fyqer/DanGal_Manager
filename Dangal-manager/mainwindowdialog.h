#ifndef MAINWINDOWDIALOG_H
#define MAINWINDOWDIALOG_H
#include <QFileSystemWatcher>
#include <QDialog>

namespace Ui {
class mainwindowdialog;
}

class mainwindowdialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindowdialog(QWidget *parent = nullptr);
    ~mainwindowdialog();
    void fileWatcher();
    void assignButtonToListView(QModelIndex index[]);
private slots:

    void DeleteEmptyLines(const std::string &FilePath);
    void on_Generate_button_clicked();
    void readFile();
    void on_PasswordListView_pressed(const QModelIndex &index);
    QString Decode(QString lineString);
    void on_pushButton_clicked();

signals:
    void readFileSingal();

private:
    QString key="5TGB&YHN7UJM(IK<";
    QString iv="!QAZ2WSX#EDC4RFV";
    int authorizedFlag=0;
    Ui::mainwindowdialog *ui;
    QFileSystemWatcher * watcher;
};

#endif // MAINWINDOWDIALOG_H
