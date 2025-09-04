#ifndef HEADER_H
#include <QString>
#include <QTextStream>
#define HEADER_H

struct Dealer{
    QString name;
    QString address;
    qint8 code;

    Dealer() : name("none"), address("none"), code(0){}
    Dealer(QString& n, QString& a, qint8 c) : name(n), address(a), code(c){}

    friend QTextStream& operator>>(QTextStream& is, Dealer& d);
    friend QTextStream& operator<<(QTextStream& os, const Dealer& d);
};

class Array{
private:
    int size;
    Dealer* mas;
public:
    Array() : size(0), mas(nullptr){}
    Array(int s) : size(s), mas(new Dealer[s]){}
    Array(const Array& other): size(other.size), mas(other.mas){}
    ~Array(){delete[] mas;}

    Dealer& operator[](int i);
    Array& operator=(const Array& other);
    void readFromFile(const QString& filename);
    void selectionSort(bool ascending);
    int getSize();
};

#endif
