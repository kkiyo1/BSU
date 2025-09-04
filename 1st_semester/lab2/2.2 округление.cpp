#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	double a, b;
	cout << "Введите первое число: ";
	cin >> a;
	cout << "Введите второе число: ";
	cin >> b;
	int a1 = round(a);
	int b1 = round(b);
	
	cout << "Частное: " << a / b << endl <<
		"Остаток от деления: " << a1 % b1;


	return 0;
}