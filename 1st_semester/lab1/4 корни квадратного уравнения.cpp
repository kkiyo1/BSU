#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	float a,b,c,x1, x2;
	cout << "Введите коэффициенты квадратного уравнения: "<< '\n';
	cin >> a >> b >> c;
	
	if (a == 0 && b!= 0 && c!=0 ) {
		x1 = (-c/ b);
		cout << "Уравнение имеет 1 корень: " << x1;
	}
	else if (a != 0 && b == 0) {
		if (c > 0) {
			cout << "Уравнение не имеет корней.";
		}
		else if (c == 0) {
			cout << "Уравнение имеет 1 корень: 0";
		}
		else {
			x1 = sqrt(( - c) / a);
			cout << "Уравнение имеет 1 корень: " << x1;
		}
	}
	else if (a == 0 && b != 0 && c == 0) {
		cout << "Урвнение имеет единственный корень: 0";
	}
	else if (a == 0 && b == 0 && c != 0) {
		cout << "Некорректное уравнение";
	}
	else if (a == 0 && b == 0 && c == 0) {
		cout << "Уравнение имеет бесконечное количество корней.";
	}
	else{


		float d = ((b * b) - (4 * a * c));
		if (d < 0) {
			cout << "Уравнение не имеет корней.\n";
		}
		else if (d == 0) {
			x1 = (-b / (2 * a));
			cout << "Уравнение имеет единственный корень: " << x1;
		}
		else {
			x1 = ((-b + sqrt(d)) / (2 * a));
			x2 = ((-b - sqrt(d)) / (2 * a));
			cout << "Уравнение имеет 2 корня: " << x1 << " и " << x2;
		}
	}
}