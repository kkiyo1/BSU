#include <iostream>
#include "header.h"

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

Array::Array(int size) : n(size), arr(new int[size]()) {}

Array::Array(const Array& other) : n(other.n), arr(new int[other.n]) {
    for (int i = 0; i < n; i++) {
        arr[i] = other.arr[i];
    }
}

Array::Array(Array&& other) noexcept : n(other.n), arr(other.arr) {
    other.arr = nullptr;
    other.n = 0;
}

Array::~Array() {
    delete[] arr;
}

int Array::getSize() { return n; }

int& Array::operator[](int index) {
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

const int& Array::operator[](int index) const {
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] arr;
        n = other.n;
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        n = other.n;
        other.arr = nullptr;
        other.n = 0;
    }
    return *this;
}

Array Array::factorials(int count) {
    if (count > n) count = n;

    for (int i = 0; i < count; i++) {
        arr[i] = factorial(i + 1);
    }
    return *this;
}

Array Array::noDuplicates() {
    if (n == 0) return Array(0);

    int* temp = new int[n];
    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < uniqueCount; j++) {
            if (temp[j] == arr[i]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            temp[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    Array result(uniqueCount);
    for (int i = 0; i < uniqueCount; i++) {
        result[i] = temp[i];
    }

    delete[] temp;
    return result;
}

void Array::print() {
    if (n == 0) {
        std::cout << "������ ����" << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) std::cout << " ";
    }
    std::cout << std::endl;
}

Node::Node(int value) : data(value), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

void LinkedList::push(int a) {
    Node* newNode = new Node(a);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void LinkedList::print() {
    if (head == nullptr) {
        std::cout << "������ ����" << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

void LinkedList::reverse() {
    auto reverseRecursive = [](Node* current, Node* prev, auto&& self) -> Node* {
        if (current == nullptr) {
            return prev;
        }

        Node* next = current->next;
        current->next = prev;
        return self(next, current, self);
        };

    head = reverseRecursive(head, nullptr, reverseRecursive);
}

Menu::Menu() : currentArr(nullptr) {}

Menu::~Menu() {
    delete currentArr;
}

void Menu::inputArray() {
    int size;
    std::cout << "������� ������ �������: ";
    std::cin >> size;
    delete currentArr;
    currentArr = new Array(size);

    std::cout << "������� " << size << " ��������� �������: ";
    for (int i = 0; i < size; i++) {
        std::cin >> (*currentArr)[i];
    }
}

void Menu::inputList() {
    int size;
    std::cout << "������� ������ ������: ";
    std::cin >> size;
    std::cout << "������� " << size << " ��������� ������: ";
    for (int i = 0; i < size; i++) {
        int num;
        std::cin >> num;
        currentList.push(num);
    }
}

void Menu::show() {
    while (true) {
        std::cout << "\n=== ���� ===" << std::endl;
        std::cout << "1. �� ���� ����������� ����� n. �� ����� ��������� � ������� n ������������." << '\n' <<
            "2. �� ���� � ��������� (������) � �������. �� ����� ���������, � ���������� ������� ���������, �� ��� ����������." << '\n' <<
            "3. ���������� ������� ������ ��������� ��������" << '\n' <<
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
            std::cout << "���������: ";
            currentArr->print();
            break;
        }
        case '2': {
            inputArray();
            std::cout << "�������� ������: ";
            currentArr->print();
            Array noDup = currentArr->noDuplicates();
            std::cout << "��� ����������: ";
            noDup.print();
            break;
        }
        case '3': {
            inputList();
            std::cout << "�������� ������: ";
            currentList.print();
            currentList.reverse();
            std::cout << "����������� ������: ";
            currentList.print();
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