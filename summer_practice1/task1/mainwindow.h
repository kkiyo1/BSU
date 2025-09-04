#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "header.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getArraySize();

private slots:
    void on_pushButton_clicked();
    void setupContextMenu();
    void showContextMenu(const QPoint &pos);
    void keyPressEvent(QKeyEvent *event) override;
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Array arr;
};
#endif // MAINWINDOW_H
