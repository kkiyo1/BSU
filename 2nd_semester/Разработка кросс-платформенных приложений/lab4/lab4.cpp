#include <iostream>
#include "header.h"
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
	DoubleLinkedList list;
	char userChoice;
	string input = "input.txt", output = "output.txt";
	list.readFromText(input);
    list.printConsole();
    do {
        menu();
        std::cin >> userChoice;
        switch (userChoice) {
        case '1': {
            Student st;
            std::cin >> st;
            list.pushFront(st);
            std::cout << "Студент добавлен в начало списка" << '\n';
            break;
        }
        case '2': {
            Student st;
            std::cin >> st;
            list.pushBack(st);
            std::cout << "Студент добавлен в начало списка" << '\n';
            break;
        }
        case '3': {
            int index;
            Student st;
            cin >> st;
            cout << "Введите индекс (начиная с 0): ";
            cin >> index;
            list.insert(st, index);
            cout << "Студент добавлен в список под индексом " << index << '\n';
            break;
        }
        case '4': {
            list.popFront();
            break;
        }
        case '5': {
            list.popBack();
            break;
        }
        case '6': {
            if (list.isEmpty()) {
                cout << "Список пуст" << '\n';
                break;
            }
            int index;
            cout << "Введите индекс" << '\n';
            cin >> index;
            list.erase(index);
            break;
        }
        case '7': {
            if (list.isEmpty()) {
                cout << "Список пуст" << '\n';
                break;
            }
            list.clearAll();
            cout << "Список очищен" << '\n';
            break;
        }
        case '8': {
            list.sort();
            break;
        }
        case '9': {
            if (list.isEmpty()) {
                cout << "Список пуст" << '\n';
                break;
            }
            list.printConsole();
            list.printFile(output);
            cout << "Список записан в файл output.txt" << '\n';
            break;
        }
        default: {
            cout << "Incorrect input" << '\n';
            break;
        }
        }
    } while (userChoice != 'b' && userChoice != 'B');

	return 0;
}