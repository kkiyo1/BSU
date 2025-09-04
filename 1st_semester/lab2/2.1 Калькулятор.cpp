#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

int factorial(int x) {
    if (x < 0) return -1; // Возвращаем -1 для отрицательных чисел
    int fact = 1;
    for (int i = 1; i <= x; i++) {
        fact *= i;
    }
    return fact;
}
double calc(int x, int y, string symb) {
    double res=0;
    if (symb == "/") res = double(x) / y;
    else if (symb == "%") res = x % y;
    else if (symb == "&") res = x & y;
    else if (symb == "|") res = x | y;
    else if (symb == "^") res = x ^ y;
    else if (symb == ">>") res = x >> y;
    else if (symb == "<<") res = x << y;
    else {
        cout << "Ошибка вводаю";
        return -1;
    }
    cout << "Результат в десятичной с/с: " << res << endl;
    cout << "Результат в восьмеричной с/с: " << std::oct << (int)res << endl;
    cout << "Результат в шестнадцатиричной с/с: " << std::hex << (int)res << endl;
    return(res);
}
double calc(int x, string symb) {
    double res=0;
    if (symb == "!") res = factorial(x);
    else if (symb == "~") res = ~x;
    cout << "Результат в десятичной с/с: " << res << endl;
    cout << "Результат в восьмеричной с/с: " << std::oct << (int)res << endl;
    cout << "Результат в шестнадцатиричной с/с: " << std::hex << (int)res << endl;
    return (res);
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string symb; // Изменяем на строку для считывания операций
    int a, b;
    bool flag = false;
    do {
        cout << "Введите операцию(/,%,&,|,^,~,!,<<,>>) или e для выхода из прграммы: ";
        cin >> symb;
        if (symb == "~" || symb == "!") {
            cout << "Введите число: ";
            cin >> a;
            calc(a, symb);
        }
        else if (symb == "E" || symb == "e") {
            flag = false;
            return 1;
        }
        else {
            cout << "Введите первое целое число: ";
            cin >> a;
            cout << "Введите второе целое число: ";
            cin >> b;
            calc(a, b, symb);
        }
    } while (!flag);
    return 0;
}