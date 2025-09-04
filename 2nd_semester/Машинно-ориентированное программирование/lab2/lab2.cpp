#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "RU");

    int n;
    cout << "Введите размерность массива: ";
    cin >> n;

    if (n > 100) {
        cout << "Слишком большой размер массива";
        return 1;
    }

    int* arr = new int[n];
    int* indexes = new int[n];
    int count = 0;

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }

    cout << "Сгенерированный массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int* A = &arr[0];
    int* B = &indexes[0];

    /*for (int i = 0; i < n; i++) {
        for (int j = 2; j < sqrt(arr[i]); j++) {
            if (arr[i] % j == 0) {
                indexes[size] = arr[i];
                size++;
                break;
            }
        }
    }*/
    //shr esi, 2 - сдвиг вправо
    int divider = 2;

    __asm {
        mov esi, A
        mov edi, B
        mov ecx, n
        mov ebx, divider
    for1:
        mov eax,[esi]
        cdq
        idiv ebx
        cmp edx, 0
        jz addNumber
        inc ebx
        cmp ebx, [esi]
        jl for1
        mov ebx, divider
        add esi, 4
        loop for1
        jmp finish

    addNumber :
        inc count
        mov edx, esi
        sub edx, A
        shr edx, 2
        mov[edi], edx
        add edi, 4
        add esi, 4
        mov ebx, divider
        loop for1
    finish:
    }

    cout << "Индексы состаных чисел: ";
    for (int i = 0; i < count; i++) {
        cout << indexes[i] << " ";
    }
    cout << endl;
    delete[] arr;
    delete[] indexes;
    return 0;
}
