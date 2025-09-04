#include "mainwindow.h"
#include "test_header.h"
#include <QTest>
#include <QApplication>

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTest::qExec(new TestInput, argc, argv);
    return a.exec();
}
