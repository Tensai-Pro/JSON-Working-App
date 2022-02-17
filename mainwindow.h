#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <student.h>

#include <QLinkedList>

#include <QFile>
#include <QFileDialog>

#include <QMessageBox>

#include <QStandardItemModel>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QJsonDocument doc;
    QJsonArray docArr;
    QJsonParseError err;

    QString path;
    QFile file;

    QLinkedList<Student> students;
    QLinkedList<Student>::Iterator iterator;

private slots:
    void on_action_triggered();

    void on_addButton_clicked();

    void on_action_2_triggered();

    void on_table_clicked(const QModelIndex &index);

    void on_changeButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *model;

    int currentRow;

    void addNewRow();
};
#endif // MAINWINDOW_H
