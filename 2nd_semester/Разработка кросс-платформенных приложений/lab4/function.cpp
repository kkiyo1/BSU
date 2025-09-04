#include <iostream>
#include "header.h"
#include <fstream>

void menu() {
	setlocale(LC_ALL, "RU");
	std::cout << "================================================================" << '\n';
	std::cout << "1. Добавить элемент в начало списка" << '\n' << "2. Добавить элемент в конец списка" << '\n' <<
		"3. Добавить элемент по индексу(начиная с 0)" << '\n' << "4. Удалить элемент из начала списка" <<
		'\n' << "5. Удалить элемент из конца списка" << '\n' << "6. Удалить элемент по индексу" << '\n' <<
		"7. Очистить список" << '\n' << "8. Сортировать список по алфавиту" << '\n' << "9. Вывести список в файл" << '\n';
	std::cout << "================================================================" << '\n';
}

Student::Student() : phone(0), code(0.0f), surname("undefined") {};

Student::Student(const std::string& s, const int& p, const double& c) : surname(s), phone(p), code(c) {}

std::ostream& operator<<(std::ostream& os, const Student& st) {
	std::cout << st.surname << " " << st.phone << " " << st.code << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Student& st) {
	std::cout << "Введите фамилию: ";
	std::cin >> st.surname;
	std::cout << "Введите телефон: ";
	std::cin >> st.phone;
	std::cout << "Введите код: ";
	std::cin >> st.code;
	return is;
}

Node::Node() : data(Student()), next(nullptr), prev(nullptr) {};

Node::Node(Student& d) : data(d), next(nullptr), prev(nullptr) {};

DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr) {};

void DoubleLinkedList::readFromText(const std::string& filename) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cerr << "error opening";
		return;
	}
	std::string str;
	while (getline(inputFile, str)) {
		size_t pos = str.find(' ');
		if (pos != std::string::npos) {
			std::string surname = str.substr(0, pos);
			size_t pos2 = str.find(' ', pos+1);
			try {
				int phone = stoi(str.substr(pos + 1, pos2 - (pos + 1)));
				double code = stod(str.substr(pos2 + 1));
				Student st(surname, phone, code);
				pushFront(st);
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing data: " << e.what() << std::endl;
				continue;
			}
		}
	}
}

bool DoubleLinkedList::isEmpty() {
	return (head == nullptr && tail == nullptr) ? 1 : 0;
}

void DoubleLinkedList::printConsole() {
	if (isEmpty()) std::cout << "Список пуст" << '\n';
	else for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) std::cout << ptr->data;
	std::cout << '\n';
}

void DoubleLinkedList::printFile(const std::string& filename) {
	std::ofstream outputFile(filename);
	if (!outputFile.is_open()) {
		std::cerr << "Error file opening" << '\n';
	}
	for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
		outputFile << ptr->data.surname << " " << ptr->data.phone << " " << ptr->data.code << '\n';
	}
	outputFile.close();
}

Node* DoubleLinkedList::pushFront(Student& st) {
	Node* ptr = new Node(st);
	ptr->next = head;
	if (head != nullptr) head->prev = ptr;
	if (tail == nullptr) tail = ptr;
	head = ptr;
	return ptr;
}

Node* DoubleLinkedList::pushBack(Student& st) {
	Node* ptr = new Node(st);
	ptr->prev = tail;
	if (tail != nullptr) tail->next = ptr;
	if (head == nullptr) head = ptr;
	tail = ptr;
	return ptr;
}

void DoubleLinkedList::popFront() {
	if (isEmpty()) std::cout << "Список пуст" << '\n';
	else std::cout << "Студент удален из начала списка" << '\n';
	if (head == nullptr) return;
	Node* ptr = head->next;
	if (ptr != nullptr) ptr->prev = nullptr;
	else tail = nullptr;
	delete head;
	head = ptr;
}

void DoubleLinkedList::popBack() {
	if (isEmpty()) std::cout << "Список пуст" << '\n';
	else std::cout << "Студент удален из конца списка" << '\n';
	if (tail == nullptr) return;
	Node* ptr = tail->prev;
	if (ptr != nullptr) ptr->next = nullptr;
	else head = nullptr;
	delete tail;
	tail = ptr;
}

Node* DoubleLinkedList::getAt(int index) {
	Node* ptr = head;
	int i = 0;
	while (i != index) {
		if (ptr == nullptr) return ptr;
		ptr = ptr->next;
		i++;
	}
	return ptr;
}

Node* DoubleLinkedList::operator[](int index) {
	return getAt(index);
}

Node* DoubleLinkedList::insert(Student& st, int index) {
	Node* right = getAt(index);
	if (right == nullptr)
		return pushBack(st);
	Node* left = right->prev;
	if (left == nullptr)
		return pushFront(st);
	Node* ptr = new Node(st);
	ptr->next = right;
	ptr->prev = left;
	left->next = ptr;
	right->prev = ptr;
	return ptr;
}

void DoubleLinkedList::erase(int index) {
	Node* ptr = getAt(index);
	if (ptr == nullptr) return;
	if (ptr->prev == nullptr) {
		popFront();
		return;
	};
	if (ptr->next == nullptr) {
		popBack();
		return;
	}
	std::cout << "Студент удален из списка" << '\n';
	Node* left = ptr->prev;
	Node* right = ptr->next;
	left->next = right;
	right->prev = left;
	delete ptr;
}

void DoubleLinkedList::clearAll() {
	while (head != nullptr) popFront();
}

void DoubleLinkedList::sort() {
	if (isEmpty()) {
		std::cout << "Список пуст" << '\n';
		return;
	}
	for (Node* ptr1 = head; ptr1 != tail; ptr1 = ptr1->next) {
		for (Node* ptr2 = ptr1->next; ptr2 != nullptr; ptr2 = ptr2->next) {
			if (ptr2->data.surname < ptr1->data.surname) {
				std::swap(ptr1->data, ptr2->data);
			}
		}
	}
}
