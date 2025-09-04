#include <iostream>
#include "header.h"

int main() {
	setlocale(LC_ALL, "RU");
	Student st1("Глеб", 1, 101);
	st1.getData();
	getCount();
	Student st2("Роман", 2, 485);
	st2.getData();
	getCount();
	//Diplomist d1("Петр", 3 , 15 , "Программирование");
	Diplomist d2("Богдан", 1, 184, "Экономика");
	d2.getData();
	d2.setTopic("Робототеника");
	d2.getData();
	getCount();
	return 0;
}	