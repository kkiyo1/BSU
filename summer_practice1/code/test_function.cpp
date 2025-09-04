#include <QTest>
#include "mainwindow.h"
#include "test_header.h"
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

TestInput::TestInput(QObject *parent) : QObject(parent)
{
}

void TestInput::checkPositive(){
    MainWindow window;
    window.show();

    auto* lineEdit = window.findChild<QLineEdit*>("lineEdit");
    auto* button = window.findChild<QPushButton*>("pushButton");
    auto* listWidget = window.findChild<QListWidget*>("listWidget");

    lineEdit->setText("5");
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(listWidget->count(), 5); //проверка что выведено ровно 5 элементов
}

void TestInput::checkString(){
    MainWindow window;
    window.show();

    auto* lineEdit = window.findChild<QLineEdit*>("lineEdit");
    auto* button = window.findChild<QPushButton*>("pushButton");
    auto* listWidget = window.findChild<QListWidget*>("listWidget");

    lineEdit->setText("any string");
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(listWidget->count(), 0);
}
