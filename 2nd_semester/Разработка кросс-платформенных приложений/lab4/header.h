#pragma once
#include <string>
#include <fstream>

void menu();

struct Student {
	int phone;
	double code;
	std::string surname;

	Student();
	Student(const std::string& surname, const int& p, const double& c);

	friend std::ostream& operator<<(std::ostream& os, const Student& st);
	friend std::istream& operator>>(std::istream& is, Student& st);
};

struct Node {
	Student data;
	Node *next, *prev;
	Node();
	Node(Student& d);
};

class DoubleLinkedList {
private:
	Node* head, * tail;
public:
	DoubleLinkedList();
	void readFromText(const std::string& filename);
	Node* pushFront(Student& st);
	Node* pushBack(Student& st);
	void popFront();
	void popBack();
	void printConsole();
	void printFile(const std::string& filename);
	Node* getAt(int index);
	Node* operator[](int index);
	Node* insert(Student& st, int index);
	void erase(int index);
	void clearAll();
	void sort();
	bool isEmpty();
};