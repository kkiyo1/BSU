#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int n; bool pr = true;
	cout << "Введите натуральное число N: ";
	cin >> n;
	if (n <= 0) cout << "Вы ввели не натуральное число.";
	else {
		for (int i = 2; i <= n; i++) {
			if (n % i == 0) {
				for (int j = 2; j <= sqrt(i); j++) {
					if (i % j == 0) pr = false;
				}
				if (pr) cout << endl <<"Простой делитель: " << i;

			}
		}
	}
	return 0;
}