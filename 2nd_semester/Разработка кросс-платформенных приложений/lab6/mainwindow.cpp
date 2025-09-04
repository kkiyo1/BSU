#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "errordialog.h"
#include <QMap>
#include <QFile>

qint8 convertTemperature(qint8 value, QString from, QString to, QString& errorMessage) {
    QMap<QString, double> toCelsius{
        {"Celsius", 1.0},
        {"Fahrenheit", 5.0 / 9.0},
        {"Kelvin", 1.0},
        {"Reaumur", 5.0 / 4.0}
    };

    QMap<QString, double> offsetToCelsius{
        {"Celsius", 0.0},
        {"Fahrenheit", -32.0},
        {"Kelvin", -273.15},
        {"Reaumur", 0.0}
    };

    if (!toCelsius.contains(from)) {
        errorMessage = "Ошибка: неизвестная исходная система!";
        return 0;
    }

    double tempCelsius = (value + offsetToCelsius[from]) * toCelsius[from];

    QMap<QString, double> fromCelsius{
        {"Celsius", 1.0},
        {"Fahrenheit", 9.0 / 5.0},
        {"Kelvin", 1.0},
        {"Reaumur", 4.0 / 5.0}
    };

    QMap<QString, double> offsetFromCelsius{
        {"Celsius", 0.0},
        {"Fahrenheit", 32.0},
        {"Kelvin", 273.15},
        {"Reaumur", 0.0}
    };

    if (!fromCelsius.contains(to)) {
        errorMessage = "Ошибка: неизвестная целевая система!";
        return 0;
    }

    double result = tempCelsius * fromCelsius[to] + offsetFromCelsius[to];

    if (result < -128 || result > 127) {
        errorMessage = "Ошибка: выход за\nпределы диапазона qint8!";
        return 0;
    }

    return static_cast<qint8>(result);
}

void writeText(const qint8& data){
    QFile output("output.txt");
    if (output.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&output);
        stream << QString::number(data);
        output.close();
    } else {
        qDebug() << "Не удалось открыть файл для записи!";
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString metrics1 = ui->comboBox->currentText();
    QString metrics2 = ui->comboBox_2->currentText();
    QString output = "output.txt";
    bool ok;
    qint8 input = static_cast<qint8>(ui->textEdit->toPlainText().toInt(&ok));

    if (!ok) {
        ErrorDialog *dialog = new ErrorDialog("Ошибка: введено не число!", this);
        dialog->exec();
        return;
    }

    QString errorMessage;
    qint8 result = convertTemperature(input, metrics1, metrics2, errorMessage);
    writeText(result);

    if (!errorMessage.isEmpty()) {
        ErrorDialog *dialog = new ErrorDialog(errorMessage, this);
        dialog->exec();
    } else {
        ui->textEdit_2->setText(QString::number(result));
    }
}
