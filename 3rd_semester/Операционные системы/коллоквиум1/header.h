#pragma once

class Array {
private:
    int n;
    int* arr;
public:
    Array(int size);
    ~Array();
    int& operator[](int index);
    const int& operator[](int index) const;
    Array factorials(int n);
    Array noDublicates(Array* arr);
    Array reverse(Array* arr);
    void print();
};

class Menu {
private:
    Array* currentArr;
public:
    Menu();
    ~Menu();
    void show();
};

int factorial(int n);