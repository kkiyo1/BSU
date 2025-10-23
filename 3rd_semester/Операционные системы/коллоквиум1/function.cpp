#include <iostream>
#include "header.h"

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

Array::Array(int size) : n(size) {
    arr = new int[n]();
}

Array::~Array() {
    delete[] arr;
}

int& Array::operator[](int index) {
    return arr[index];
}

const int& Array::operator[](int index) const {
    return arr[index];
}

Array Array::factorials(int count) {
    if (count > n) count = n;

    for (int i = 0; i < count; i++) {
        arr[i] = factorial(i + 1);
    }
    return *this;
}

Array Array::noDublicates(Array* arr) {
    return *this;
}

Array Array::reverse(Array* arr) {
    return *this;
}

void Array::print() {
    for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
    std::cout << std::endl;
}

Menu::Menu() : currentArr(nullptr) {}

Menu::~Menu() {
    delete currentArr;
}

void Menu::show() {
    while (true) {
        std::cout << "\n=== ���� ===" << std::endl;
        std::cout << "1. �� ���� ����������� ����� n. �� ����� ��������� � ������� n ������������." << '\n' <<
            "2. �� ���� � ��������� (������) � �������. �� ����� ���������, � ���������� ������� ���������, �� ��� ����������." << '\n' <<
            "3. ���������� ������� ������ ��������� ��������." << '\n' <<
            "4. �����" << '\n' <<
            "����: ";

        char choice;
        std::cin >> choice;

        switch (choice) {
        case '1': {
            int n;
            std::cout << "������� n: ";
            std::cin >> n;
            delete currentArr;
            currentArr = new Array(n);
            currentArr->factorials(n);
            currentArr->print();
            break;
        }
        case '2': {
            break;
        }
        case '3': {
            break;
        }
        case '4':
            std::cout << "�����..." << std::endl;
            return;
        default:
            std::cout << "�������� ����!" << '\n';
        }
    }
}