#ifndef HEADER_H
#define HEADER_H

#include <iostream>

class Vector {
public:
    double x;
    double y;

    Vector(double a = 0, double b = 0);
    Vector(const Vector& v);
    ~Vector();

    friend Vector operator~(const Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
    friend std::istream& operator>>(std::istream& is, Vector& v);
    friend Vector operator+(const Vector& v1, const Vector& v2);
    friend Vector operator-(const Vector& v1, const Vector& v2);
    friend double operator*(const Vector& v1, const Vector& v2);
    friend Vector operator*(const Vector& v1, const double a);

    Vector& operator++();
    Vector& operator++(int);
    Vector& operator--();
    Vector& operator--(int);
    Vector operator=(const Vector& v);
    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);
};

class Container {
public:
    static const int MAX_SIZE = 100;
    int size;
    Vector* arr;

    Container();
    ~Container();
    void addToContainer(const Vector& v);
    const Vector& operator[](int index) const;
};

#endif
