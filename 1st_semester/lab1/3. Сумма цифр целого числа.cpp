#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int a, summ =0;
	cout << "Введите целое число: ";
	cin >> a;
	if (a == 0) cout << "Сумма = 0";
	else {
		for (int i = 0; a %10 != 0; i++) {
			summ += a % 10;
			a /= 10;
		}
		if (summ < 0) summ *= (-1);
		cout << endl << "Сумма цифр вашего числа: " << summ;
	}

	return 0;
}