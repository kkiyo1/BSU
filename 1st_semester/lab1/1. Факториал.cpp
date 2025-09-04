#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int a, f=1;
	cout << "Введите натуральное число: ";
	cin >> a;
	if (a >= 1) {
		for (int i = 1; i <= a; i++) {
			f *= i;
		}
		cout << endl << "Факториал числа " << a << ": " << f;
		return 0;
	}
	else if (a <= 0) cout << "Вы ввели не натуральное число";
}