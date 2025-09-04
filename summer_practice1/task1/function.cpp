#include "header.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Dealer& Array::operator[](int i) {
    return mas[i];
}

QTextStream& operator>>(QTextStream& is, Dealer& d) {
    is >> d.name >> d.address;
    int tempCode;
    is >> tempCode;
    d.code = static_cast<qint8>(tempCode);
    return is;
}

QTextStream& operator<<(QTextStream& os, const Dealer& d) {
    os << d.name << " " << d.address << " " << static_cast<int>(d.code) << '\n';
    return os;
}

int Array::getSize(){ return this->size; }

Array& Array::operator=(const Array& other){
    if(this != &other){
        delete[] mas;
        size = other.size;
        mas = new Dealer[size];
        std::copy(other.mas, other.mas + size, mas);
    }
    return *this;
}

void Array::readFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Ошибка при открытии файла";
        return;
    }
    //qDebug() << "all fine";
    QTextStream in(&file);
    for(int i=0; i < this->size; i++){
        in >> mas[i];
    }
    file.close();
}

void Array::selectionSort(bool ascending) {
    for (int i = 0; i < size - 1; ++i) {
        int extremeIndex = i;
        for (int j = i + 1; j < size; ++j) {
            bool condition = ascending ?
                                 (mas[j].name < mas[extremeIndex].name) :
                                 (mas[j].name > mas[extremeIndex].name);
            if (condition) {
                extremeIndex = j;
            }
        }
        if (extremeIndex != i) {
            std::swap(mas[i], mas[extremeIndex]);
        }
    }
}
