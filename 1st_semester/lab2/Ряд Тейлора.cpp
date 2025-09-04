#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    long double x, slag, sum = 1.f;
    int k, n = 0;

    cout << "Введите значение x: ";
    cin >> x;
    cout << "Введите значение k (для вычисления epsilon = 10^-k): ";
    cin >> k;
    if (k <= 0) {
        cout << "Вы ввели не натуральное число k";;
        return 1;
    }

    long double epsilon = pow(10, -k);
    long double fact = 1;
    do {
        fact *= n + 1;
        slag = pow(x, n+1) / fact;
        sum += slag;
        n++;
    } while (fabs(slag) > epsilon);

    cout << "Приближённое значение e^x по ряду Тейлора: " << sum << endl;

    cout << "Точное значение e^x: " << exp(x) << endl;

    return 0;
}
