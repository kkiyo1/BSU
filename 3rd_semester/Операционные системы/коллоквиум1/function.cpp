#include <iostream>
#include "header.h"

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

bool isValidSize(int& size) {
    std::cin >> size;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "����������, ������� ����� �����." << '\n';
        size = -1;
        return 0;
    }
    else if (size <= 0) {
        std::cout << "������ ������ ���� ������������� ������!" << '\n';
        return 0;
    }

    return 1;
}

bool isValidListElement(int& element, int index) {
    std::cin >> element;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������! ����������, ������� ����� ����� ��� �������� " << (index + 1) << '\n';
        return false;
    }

    return true;
}


//=======================================Array======================================================

Array::Array(int size) : n(size), arr(new int[size]) {}

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

void Array::input() {
    for (int i = 0; i < n; i++) {
        int num;

        do {
            std::cout << "������� " << i + 1 << " ������� �������: ";
        } while (!isValidListElement(num, i));

        arr[i] = num;
    }
}

void Array::print() const {
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

void Array::reverse() {
    Array result(n);
    auto reverseRecursive = [&](int start, int end, auto&& self) -> void {
        if (start >= end) return;
        result.arr[start] = this->arr[end - 1];
        result.arr[end - 1] = this->arr[start];
        self(start + 1, end - 1, self);
        };

    reverseRecursive(0, n, reverseRecursive);
    *this = result;
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

//=======================================LinkedList==============================================

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

void LinkedList::input() {
    int listSize = -1;
    do {
        std::cout << "������� ������ ������: ";
    } while (!isValidSize(listSize));

    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;

    for (int i = 0; i < listSize; i++) {
        int num;

        do {
            std::cout << "�������" << i + 1 << "������� ������: ";
        } while (!isValidListElement(num, i));

        push(num);
    }
}

void LinkedList::print() const {
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

//=============================================Menu=================================================
Menu::Menu() : currentContainer(nullptr), currentArr(nullptr) {}

Menu::~Menu() {
    delete currentArr;
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
            do {
                if (!isValidSize(n)) {
                    continue;
                }
                else if (n > 12) {
                    std::cout << "����� �� ������ ��������� 12 (��������� �������� ����� �� ���������� � int): ";
                }
                else {
                    break;
                }
            } while (true);

            delete currentArr;
            currentArr = new Array(n);
            currentArr->factorials(n);
            std::cout << "���������: ";
            currentArr->print();
            break;
        }
        case '2': {
            int arrSize = -1;
            do {
                std::cout << "������� ������ �������: ";
            } while (!isValidSize(arrSize));
            delete currentArr;
            currentArr = new Array(arrSize);
            currentArr->input();
            std::cout << "�������� ������: ";
            currentArr->print();
            Array noDup = currentArr->noDuplicates();
            std::cout << "��� ����������: ";
            noDup.print();
            break;
        }
        case '3': {
            currentList.input();
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