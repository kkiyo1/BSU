#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
//hoare sort
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr[j], arr[i]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return(i + 1);
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);

	}
}

//qsort
int compare(const void* a, const void* b) {
	return(*(int*)b - *(int*)a);
}
void searchElement(int &el, int *arr, int &n) {
	int* found = (int*)bsearch(&el, arr, n, sizeof(arr[0]), compare);
	if (found != nullptr) {
		int index = found - arr;
		cout << "Ваш элемент находится в массиве под индексом " << index << endl;
	}
	else {
		cout << "Элемент не найден." << endl;
	}
}

void input(int*& arr, int &n) {
	cout << "Введите количество элементов массива: ";
	cin >> n;
	if (n <= 0) {
		cout << "Ошибка создания массива";
		exit(0);
	}
	arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100 + 1;
	}
}
void output(int* arr, int n) {
	cout << "Исходный массив: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(0));
	int n;
	int* arr = nullptr;
	input(arr, n);
	output(arr, n);
	qsort(arr, n, sizeof(n), compare);
	cout << '\n' << "Отсортированный по убыванию массив: ";
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';
	//quickSort(arr, 0, n - 1);
	sort(arr, arr + n);
	cout << '\n' << "Отсортированный по возрастанию массив: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	int el;
	cout << '\n' << "Введите элемент который надо найти: ";
	cin >> el;
	searchElement(el, arr, n);
	delete[] arr;
	return 0;
}


