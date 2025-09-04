#include <iostream>

using namespace std;


int main() {
    setlocale(LC_ALL, "RU");
    int a, b;
    cout << "Введите 2 числа: ";
    cin >> a >> b;
    int c = a * b;
    if (a <= 0 || b <= 0) cout << "Среди этих чисел есть не натуральные";
    while (a != b) {
        if (a > b) {
            a -= b;
        }
        else {
            b -= a;
        }
    }
    cout << "НОК = " << c/a << endl << "НОД = " << a;
    return 0;
}