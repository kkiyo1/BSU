#include <iostream>
#include <iomanip>
#include "header.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    Container container;
    Vector v1, v2, v3;


    cout << "Введите координаты вектора A: ";
    cin >> v1;
    container.addToContainer(v1);

    cout << "Введите координаты вектора B: ";
    cin >> v2;
    container.addToContainer(v2);

    cout << endl << "A = " << container[0] << " B = " << container[1];
    cout << endl << "A + B = " << container[0] + container[1];
    cout << endl << "A - B = " << container[0] - container[1];
    cout << endl << "A * B = " << container[0] * container[1];
    cout << endl << "A * 5 " << container[0] * 5;
    v3 = ++v1;
    cout << endl << "++A = " << v1;
    cout << endl << "++A = " << v3;
    v3 = v2++;
    cout << endl << "A++ = " << v2;
    cout << endl << "B++ = " << v3;
    --v1;
    v2--;
    cout << endl << "++A = " << v1;
    cout << endl << "B++ = " << v2;

    cout << endl << "A = B = " << v2;
    cout << endl << "-A = " << ~container[0] << " -B = " << ~container[1] << endl;
    (v1 != v2) ? cout << "Не равны" : cout << "Равны";
    return 0;
}