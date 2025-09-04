#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &MainWindow::customContextMenuRequested, this, &MainWindow::showContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getArraySize() { return arr.getSize(); };

void MainWindow::showContextMenu(const QPoint &pos) {
    QMenu menu(this);
    QAction *helpAction = menu.addAction("Помощь");
    QAction *aboutAction = menu.addAction("О программе");

    connect(helpAction, &QAction::triggered, this, []() {
        QMessageBox::information(nullptr, "Помощь", "Это контекстное меню помощи");
    });

    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "О программе", "Программа v1.0, 2025");
    });

    menu.exec(mapToGlobal(pos));
}

void MainWindow::setupContextMenu() {
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu menu;
        QAction *deleteAction = menu.addAction("Delete Item");
        connect(deleteAction, &QAction::triggered, this, [this, pos]() {
            QListWidgetItem *item = ui->listWidget->itemAt(pos);
            if (item) delete item;
        });
        menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));
    });
}
void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int n = ui->lineEdit->text().toInt(&ok);

    if (!ok || n <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное положительное число!");
        return;
    }
    arr = Array(n);
    arr.readFromFile("C:\\Users\\user\\Desktop\\task1\\input.txt");

    ui->listWidget->clear();
    for (int i = 0; i < n; ++i) {
        Dealer dealer = arr[i];
        QString itemText = dealer.name + " " + dealer.address + " " + QString::number(dealer.code);
        ui->listWidget->addItem(itemText);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        on_pushButton_clicked();
    }
    if (event->key() == Qt::Key_H) {
        QMessageBox::information(this, "Help",
                                 "Программа для работы с массивами дилеров.\n\n"
                                 "1. Введите размер массива и нажмите 'Подтвердить'\n"
                                 "2. Используйте кнопки для сортировки и управления\n"
                                 "3. Правый клик - контекстное меню");
    }
    QMainWindow::keyPressEvent(event);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString sortType = ui->comboBox->currentText();
    bool ascending = (sortType == "По возрастанию");
    arr.selectionSort(ascending);

    //qDebug() << "Sorted in " << (ascending ? "ascending" : "descending") << "order";

    ui->listWidget->clear();
    for (int i = 0; i < arr.getSize(); ++i) {
        Dealer dealer = arr[i];
        QString itemText = dealer.name + " " + dealer.address + " " + QString::number(dealer.code);
        ui->listWidget->addItem(itemText);
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
}
