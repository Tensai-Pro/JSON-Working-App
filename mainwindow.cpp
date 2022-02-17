#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->isSuspended->addItems(QStringList({"нет", "да"}));

    ui->name->setValidator(new QRegularExpressionValidator(QRegularExpression("[a-zA-zа-яА-я\\s]{1,}")));
    ui->age->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d{2}")));
    ui->averScore->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d{1}\\.\\d{1}")));

    model = new QStandardItemModel(nullptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    if (path.isEmpty())
        path = QFileDialog::getOpenFileName(nullptr, "", "C:\\", "*.json");
    else
        path = QFileDialog::getOpenFileName(nullptr, "", path, "*.json");
    file.setFileName(path);

    if (file.open(QIODevice::ReadOnly))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &err);
        file.close();

        if(err.errorString().toInt() == QJsonParseError::NoError)
        {
            students.clear();
            model->clear();
            model->setHorizontalHeaderLabels(QStringList({"Имя", "Возраст", "Средняя успеваемость", "Отстранен"}));

            docArr = doc.array();
            for (int i = 0; i < docArr.size(); i++)
            {
                QJsonObject tempObj = docArr.at(i).toObject();

                QString name = tempObj.value("name").toString();
                int age = tempObj.value("age").toInt();
                double averScore = tempObj.value("averScore").toDouble();
                bool isSuspended = tempObj.value("isSuspended").toBool();

                Student student = Student(name, age, averScore, isSuspended);
                students.append(student);

                addNewRow();
            }

            ui->table->setModel(model);
            ui->table->setColumnWidth(0, ui->table->width()/2);
            ui->table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
            ui->table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
            ui->table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

        }
        else
        {
            QMessageBox::information(nullptr, "Внимание", "Не удалось открыть файл.");
        }
    }
    else
    {
        QMessageBox::information(nullptr, "Внимание", "Не удалось открыть файл.");
    }
}



void MainWindow::on_addButton_clicked()
{
    if (ui->name->text().isEmpty() || ui->age->text().isEmpty() || ui->averScore->text().isEmpty())
    {
        QMessageBox::information(nullptr, "Внимание", "Не все поля заполнены.");
    }
    else
    {
        if (doc.isEmpty())
        {
            model->setHorizontalHeaderLabels(QStringList({"Имя", "Возраст", "Средняя успеваемость", "Отстранен"}));
        }

        QString name = ui->name->text();
        int age = ui->age->text().toInt();
        double averScore = ui->averScore->text().toDouble();
        bool isSuspended = ui->isSuspended->currentText() == "нет" ? false : true;

        ui->name->clear();
        ui->age->clear();
        ui->averScore->clear();
        ui->isSuspended->setCurrentText("нет");

        Student student = Student(name, age, averScore, isSuspended);
        students.append(student);

            /* Обновляем документ */
        QVariantMap map;
        map.insert("name", students.last().getName());
        map.insert("age", students.last().getAge());
        map.insert("averScore", students.last().getAverScore());
        map.insert("isSuspended", students.last().getIsSuspended());

        QJsonObject obj = QJsonObject::fromVariantMap(map);

        docArr.append(obj);
        doc.setArray(docArr);
             /* Конец работы с документом */

        addNewRow();

        ui->table->setModel(model);
        ui->table->setColumnWidth(0, ui->table->width()/2);
        ui->table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        ui->table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    }
}


void MainWindow::addNewRow()
{
    QStandardItem *item1 = new QStandardItem(students.last().getName());
    QStandardItem *item2 = new QStandardItem(QString::number(students.last().getAge()));
    QStandardItem *item3 = new QStandardItem(QString::number(students.last().getAverScore()));
    QStandardItem *item4 = new QStandardItem(students.last().getIsSuspended() ? "да" : "нет");

    model->appendRow(QList<QStandardItem*>({item1, item2, item3, item4}));
}


void MainWindow::on_action_2_triggered()
{
    if (path.isEmpty())
        path = QFileDialog::getSaveFileName(nullptr, "", "C:\\", "*.json");
    else
        path = QFileDialog::getSaveFileName(nullptr, "", path, "*.json");
    file.setFileName(path);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
    else
    {
        QMessageBox::information(nullptr, "Внимание", "Не удалось открыть файл.");
    }
}


void MainWindow::on_table_clicked(const QModelIndex &index)
{
    QStandardItem *clickedItem = model->itemFromIndex(index);
    currentRow = clickedItem->row();

    ui->name->setText(model->item(currentRow, 0)->text());
    ui->age->setText(model->item(currentRow, 1)->text());
    ui->averScore->setText(model->item(currentRow, 2)->text());
    ui->isSuspended->setCurrentText(model->item(currentRow, 3)->text() == "нет" ? "нет" : "да");
}



void MainWindow::on_changeButton_clicked()
{
    if (ui->name->text().isEmpty() || ui->age->text().isEmpty() || ui->averScore->text().isEmpty())
    {
        QMessageBox::information(nullptr, "Внимание", "Не все поля заполнены.");
    }
    else
    {
        QString name = ui->name->text();
        QString age = ui->age->text();
        QString averScore = ui->averScore->text();
        QString isSuspended = ui->isSuspended->currentText();

        model->item(currentRow, 0)->setText(name);
        model->item(currentRow, 1)->setText(age);
        model->item(currentRow, 2)->setText(averScore);
        model->item(currentRow, 3)->setText(isSuspended);

        ui->name->clear();
        ui->age->clear();
        ui->averScore->clear();
        ui->isSuspended->setCurrentText("нет");


        iterator = students.begin();
        for (int i = 0; i < currentRow; i++)
            iterator++;

        iterator->setName(name);
        iterator->setAge(age.toInt());
        iterator->setAverScore(averScore.toDouble());
        iterator->setIsSuspended(isSuspended == "нет" ? false : true);



        QJsonObject tempObj = {
                                {"name", name},
                                {"age", age.toInt()},
                                {"averScore", averScore.toDouble()},
                                {"isSuspended", isSuspended == "нет" ? false : true}
                              };

        docArr.replace(currentRow, tempObj);

        doc.setArray(docArr);
    }
}


void MainWindow::on_deleteButton_clicked()
{
    model->removeRow(currentRow);

    ui->name->clear();
    ui->age->clear();
    ui->averScore->clear();
    ui->isSuspended->setCurrentText("нет");

        
    iterator = students.begin();
    for (int i = 0; i < currentRow; i++)
        iterator++;


    students.erase(iterator);

    docArr.removeAt(currentRow);

    doc.setArray(docArr);
}



