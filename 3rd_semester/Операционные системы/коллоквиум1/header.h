#pragma once
#include <iostream>

class Container {
public:
    virtual ~Container() = default;
    virtual void input() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual int getSize() const = 0;
};

class Array : public Container {
private:
    int n;
    int* arr;
public:
    Array(int size = 0);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    void input() override;
    void print() const override;
    void reverse() override;
    int getSize() const override { return n; }

    int& operator[](int index);
    const int& operator[](int index) const;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    Array factorials(int count);
    Array noDuplicates();
};

class Node {
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList : public Container {
private:
    Node* head;
    int size;
public:
    LinkedList();
    ~LinkedList();

    void input() override;
    void print() const override;
    void reverse() override;
    int getSize() const override { return size; }

    void push(int a);
};

class Menu {
private:
    Container* currentContainer;
    Array* currentArr;
    LinkedList currentList;
public:
    Menu();
    ~Menu();
    void show();
};

int factorial(int n);
bool isValidSize(int& size);