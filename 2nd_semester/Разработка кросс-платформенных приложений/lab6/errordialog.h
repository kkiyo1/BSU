#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QString message, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Ошибка");
        setModal(true);

        QLabel *label = new QLabel(message, this);
        label->setGeometry(10, 10, 200, 30);

        QPushButton *closeButton = new QPushButton("Закрыть", this);
        closeButton->setGeometry(70, 50, 100, 30);
        connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    }
};

#endif
