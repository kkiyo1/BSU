#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	int n, l;
	cout << "Введите размер L верхней стороны трапеции и N количество строк: ";
	cin >> l >> n;
	if (n <= 0 || l <= 0) cout << "Ошибка. Некорректное условие";
	else if (l == 1) cout << "Минимальная длина верхней стороны: 2";
	else{
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < l+i ; j++) {
				cout << '*';
			}
			cout << endl;
		}
	}
	return 0;
}