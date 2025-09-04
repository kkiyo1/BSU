#include <iostream>
#include "header.h"

void getCount() { std::cout << "Количество классов-наследников: " << count << '\n'; };

Human::Human() : id(0),  name("Имя не установлено") {};

Human::Human(const std::string& n) : name(n), id(0) {};

Human::Human(const std::string& n, const int& i) : name(n) , id(i){};

Human::~Human() {};

void Human::getData() { std::cout << "Имя: " << name; };

Student::Student() : Human(), course(0) { count++; };

Student::Student(const Student& st) : Student(st.name, st.id, st.course) { count++; };

Student::Student(const std::string& n, const int& c, const int& i) : Human(n,i), course(c) { count++; };

Student::~Student() { count--; };

void Student::getData() {
    std::cout << "Имя: " << this->name << '\n' << "Курс: " << this->course << '\n' << "ID: " << this->id << '\n';
}

Diplomist::Diplomist() {};

Diplomist::Diplomist(const std::string& n, const int& c, const int& i, const std::string& t) : Student(n, c, i), topic(t){};

Diplomist::Diplomist(const Student& st) : Student(st) {};

Diplomist::Diplomist(const Student& st, const std::string& t) : Student(st), topic(t) {};

Diplomist::~Diplomist() { count--; };

void Diplomist::getData() {
    std::cout << "Имя: " << this->name << '\n' << "Курс: " << this->course << '\n' << "ID: " << this->id << '\n' 
        << "Тема диплома: " << this-> topic << '\n';
}

void Diplomist::setTopic(const std::string& s) {
    this->topic = s;
}