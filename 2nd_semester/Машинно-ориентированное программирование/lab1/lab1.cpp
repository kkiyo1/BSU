#include <iostream>
#include <cmath>

using namespace std;

//Y=(3+x^3/7*a*a +x/2)/ (3x^2 -7a +b)
// a=1, b=-38, x =4 f =3

void count(__int8& a, __int8& b, __int8& x) {
	cout << "Результат на C++: " << ((pow(x, 3) + 3) / (7 * pow(a, 2)) + x / 2) / (3 * pow(x, 2) - 7 * a + b) << '\n';
}

void count(__int16& a, __int16& b, __int16& x) {
	cout << "Результат на C++: " << ((pow(x, 3) + 3) / (7 * pow(a, 2)) + x / 2) / (3 * pow(x, 2) - 7 * a + b) << '\n';
}

void count(__int32& a, __int32& b, __int32& x) {
	cout << "Результат на С++: " << ((pow(x, 3) + 3) / (7 * pow(a, 2)) + x / 2) / (3 * pow(x, 2) - 7 * a + b) << '\n';
}


void asmCount8() {
	__int8 a, b, x, tempResult;
	short a0, b0, x0;
	bool zeroDivide = 0, overFlow = 0;
	cout << "Введите a, b, x" << '\n';
	cin >> a0 >> b0 >> x0;
	a = a0; b = b0; x = x0;
	__asm {
		mov al, a
		imul al
		jo metka2
		mov bl, 7
		imul bl
		jo metka2
		mov tempResult, al
		cmp tempResult, 0
		jz metka1
		mov al, x
		imul al
		jo metka2
		imul x
		jo metka2
		add al, 3
		jo metka2
		cbw
		idiv tempResult
		mov tempResult, al 
		xor al, al
		mov al, x
		cbw
		mov bl, 2
		idiv bl
		add tempResult, al
		jo metka2
		xor al, al
		mov al, x
		imul al
		jo metka2
		mov bl, 3
		imul bl
		jo metka2
		mov bl, al
		mov al, a
		mov cl, 7
		imul cl
		jo metka2
		sub bl, al
		add bl, b
		jo metka2
		xor al, al
		mov al, tempResult
		cbw
		idiv bl
		jmp metka3
	metka1 :
		mov zeroDivide, 1
		jmp metka3
	metka2:
		mov overFlow, 1
	metka3 :
		mov tempResult, al
	}
	if (zeroDivide) cout << "Ошибка деления на 0" << '\n';
	else if (overFlow) cout << "Ошибка переполнения " << '\n';
	else {
		cout << "Результат на ассемблере: " << static_cast<short>(tempResult) << '\n';
		count(a, b, x);
	}
}

void asmCount16() {
	__int16 a, b, x, tempResult;
	bool zeroDivide = 0, overFlow = 0;
	cout << "Введите a, b, x"<< '\n';
	cin >> a >> b >> x;
	__asm {
		mov ax, a
		imul ax
		jo metka2
		mov bx, 7
		imul bx
		jo metka2
		mov tempResult, ax
		cmp tempResult, 0
		jz metka1
		mov ax, x
		imul ax
		jo metka2
		imul x
		jo metka2
		add ax, 3
		jo metka2
		cwd
		idiv tempResult
		mov tempResult, ax
		xor ax, ax
		mov ax, x
		cwd
		mov bx, 2
		idiv bx
		add tempResult, ax
		jo metka2
		xor ax, ax
		mov ax, x
		imul ax
		jo metka2
		mov bx, 3
		imul bx
		jo metka2
		mov bx, ax
		mov ax, a
		mov cx, 7
		imul cx
		jo metka2
		sub bx, ax
		add bx, b
		jo metka2
		xor ax, ax
		mov ax, tempResult
		cwd
		idiv bx
		jmp metka3
	metka1 :
		mov zeroDivide, 1
		jmp metka3
	metka2 :
		mov overFlow, 1
	metka3 :
		mov tempResult, ax
	}
	if (zeroDivide) cout << "Ошибка деления на 0" << '\n';
	else if(overFlow) cout << "Ошибка переполнения " << '\n';
	else {
		cout << "Результат на ассемблере: " << tempResult << '\n';
		count(a, b, x);
	}
}

void asmCount32() {
	__int32 a, b, x, tempResult;
	bool zeroDivide = 0, overFlow = 0;
	cout << "Введите a, b, x" << '\n';
	cin >> a >> b >> x;
	__asm {
		mov eax, a
		imul eax
		jo metka2
		mov ebx, 7
		imul ebx
		jo metka2
		mov tempResult, eax
		cmp tempResult, 0
	
		jz metka1
		mov eax, x
		imul eax
		jo metka2
		imul x
		jo metka2
		add eax, 3
		jo metka2
		cdq
		idiv tempResult
		mov tempResult, eax
		xor eax, eax
		mov eax, x
		cdq
		mov ebx, 2
		idiv ebx
		add tempResult, eax
		jo metka2
		xor eax, eax
		mov eax, x
		imul eax
		jo metka2
		mov ebx, 3
		imul ebx
		jo metka2
		mov ebx, eax
		mov eax, a
		mov ecx, 7
		imul ecx
		jo metka2
		sub ebx, eax
		add ebx, b 
		jo metka2
		xor eax, eax
		mov eax, tempResult
		cdq
		idiv ebx
		jmp metka3
	metka1 :
		mov zeroDivide, 1
		jmp metka3
	metka2 :
		mov overFlow, 1
	metka3 :
		mov tempResult, eax
	}
	if (zeroDivide) cout << "Ошибка деления на 0" << '\n';
	else if (overFlow) cout << "Ошибка переполнения " << '\n';
	else {
		cout << "Результат на ассемблере: " << tempResult << '\n';
		count(a, b, x);
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	char userChoice;
	cout << "====================================================" << '\n';
	do {
		cout << "Выберите тип данных: int8, int16, int32 (1, 2, 3): "<< '\n' << "Для выхода введите b" << '\n';
		cin >> userChoice;
		switch (userChoice) {
		case '1': asmCount8(); break;
		case '2': asmCount16(); break;
		case '3': asmCount32(); break;
		case 'b': cout << "Завершение программы" << '\n'; break;
		default: cout << "Неверный ввод" << '\n'; break;
		}
		cout << "====================================================" << '\n';
	} while (userChoice != 'b');
	return 0;
}