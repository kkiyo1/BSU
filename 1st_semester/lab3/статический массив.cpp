#include <iostream>
#include <time.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));
    const int n = 10;
    int arr[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10 + 1;
    }
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    bool counted[n] = { false }; // Массив для отслеживания уже подсчитанных элементов

    cout << "Повторяющиеся элементы и их количество:" << endl;
    for (int i = 0; i < n; ++i) {
        if (!counted[i]) {
            int count = 1;
            for (int j = i +1; j < n; ++j) {
                if (arr[i] == arr[j]) {
                    count++;
                    counted[j] = true;
                }
            }
            if (count > 1) {
                cout << "Элемент " << arr[i] << " встречается " << count << " раз." << endl;
            }
        }
    }
    return 0;
}