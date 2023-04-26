#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileSystemWatcher>
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fileWatcher();
    void assignButtonToListView(QModelIndex index[]);
private slots:
    void on_Generate_button_clicked();
    void readFile();
    void on_PasswordListView_pressed(const QModelIndex &index);

signals:
    void readFileSingal();
private:
    Ui::MainWindow *ui;
    QFileSystemWatcher * watcher;
};
#endif // MAINWINDOW_H
