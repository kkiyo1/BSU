#include <iostream>
#include <list>
#include <map>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <random>
#include <iterator>

using namespace std;

void menu() {
    cout << endl << "1. Просмотреть состояния списка"
        << endl << "2. Добавить элемент"
        << endl << "3. Удалить элемент"
        << endl << "4. Слияние двух списков"
        << endl << "5. Посчитать количество элементов Х"
        << endl << "6. Выход из программы";
}

void displayList(const list<string>& my_list) {
    cout << endl << "Ваш список: " << endl;
    copy(my_list.begin(), my_list.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

bool isEqual(const string& s, const string& count_string) {
    return (s == count_string);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    list<string> my_list = { "апельсин", "яблоко", "банан" };

    int userChoice;
    string add_string, delete_string, count_string, new_list_string;
    list<string> second_list;
    int count = 0;

    do {
        menu();
        cout << endl << "Выберите действие: ";
        cin >> userChoice;
        cin.ignore();

        switch (userChoice) {
        case 1:
            displayList(my_list);
            break;
        case 2:
            cout << "Введите строку для добавления: ";
            getline(cin, add_string);
            my_list.push_back(add_string);
            break;
        case 3:
            cout << "Введите элемент, который хотите удалить: ";
            getline(cin, delete_string);
            my_list.remove(delete_string);
            break;
        case 4:
            cout << "Введите через пробел элементы вашего списка: ";
            getline(cin, new_list_string);
            {
                istringstream iss(new_list_string);
                string item;
                while (iss >> item) {
                    second_list.push_back(item);
                }
                my_list.sort();
                second_list.sort();
                my_list.merge(second_list);
                second_list.clear();
                displayList(my_list);
            }
            break;
        case 5:
            cout << "Введите элемент, который хотите посчитать: ";
            getline(cin, count_string);
            count = count_if(my_list.begin(), my_list.end(),
                [&count_string](const string& s) { return isEqual(s, count_string); });
            cout << endl << "Элемент " << count_string << " встречается " << count << " раз/раза" << endl;
            break;
        case 6:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Некорректный ввод" << endl;
        }
    } while (userChoice != 6);

    return 0;
}
