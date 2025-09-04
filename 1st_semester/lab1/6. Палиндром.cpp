#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int a, reverse = 0;
	cout << "Введите число: ";
	cin >> a;
	int с = a;
	if (a <= 0) cout << "Вы ввели не натуральное число";
	for (int i = 0; a % 10 != 0;  i++) {
		reverse = (reverse*10)+(a%10);
		a /= 10;
	}
	if (reverse == с) cout << endl << "Ваше число - палиндром";
	else cout << endl << "Ваше число не палиндром";
	return 0;
}