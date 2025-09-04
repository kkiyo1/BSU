#include <iostream>
#include <cmath>
using namespace std;

int main(){
    setlocale(LC_ALL,"RU");
    double x, n;
    cout << "Введите число и степепень: ";
    cin >> x >> n;
    if (x == 0 && n < 0) cout << "Ошибка. Нельзя возвести 0 в отрицательную степень";
    else cout << '\n' << x<<" в степени " <<n<< " = " << pow(x, n);
    return 0;
}
