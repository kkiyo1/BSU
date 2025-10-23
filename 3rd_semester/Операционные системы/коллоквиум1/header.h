#pragma once

class Array {
private:
    int n;
    int* arr;
public:
    Array(int size);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();
    int getSize();
    int& operator[](int index);
    const int& operator[](int index) const;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    Array factorials(int count);
    Array noDuplicates();
    void print();
};

class Node {
public:
    int data;
    Node* next;
    Node(int value);
};

class LinkedList {
private:
    Node* head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    void push(int a);
    void print();
    void reverse();
    int getSize() const { return size; }
};

class Menu {
private:
    Array* currentArr;
    LinkedList currentList;
public:
    Menu();
    ~Menu();
    void show();
    void inputArray();
    void inputList();
};

int factorial(int n);