#include <iostream>

int n;
int* arr;
int* check;
int* nextIndexes;

int jump(int pos) {
	//jump(n) = arr[n] + max(jump(n+2), jump(n+3))
	//все результаты jump(n) запоминаются в check[n]

	if (pos >= n) return -1;
	if (-1 != check[pos]) return check[pos];
	if (n - 1 == pos) {
		check[pos] = arr[pos];
		nextIndexes[pos] = -1;
		return check[pos];
	}

	int maxVal = -1;
	int bestNextIndex = -1;

	if (pos + 2 < n) {
		int val2 = jump(pos + 2);
		if (-1 != val2 && val2 > maxVal) {
			maxVal = val2;
			bestNextIndex = pos + 2;
		}
	}
	if (pos + 3 < n) {
		int val3 = jump(pos + 3);
		if (-1 != val3 && val3 > maxVal) {
			maxVal = val3;
			bestNextIndex = pos + 3;
		}
	}

	if (-1 != maxVal) {
		check[pos] = arr[pos] + maxVal;
		nextIndexes[pos] = bestNextIndex;
	}
	else {
		check[pos] = -1;
	}

	return check[pos];
}

int main() {
	std::cin >> n;
	if (1 == n) {
		int result;
		std::cin >> result;
		std::cout << result << '\n' << 1;
		return 0;
	}

	if (n <= 2) {
		std::cout << -1;
		return 0;
	}
	arr = new int[n];
	check = new int[n];
	nextIndexes = new int[n];

	for (int i = 0; i < n;i++) {
		std::cin >> arr[i];
		check[i] = -1;
		nextIndexes[i] = -1;
	}
	
	int result = jump(0);
	if (-1 == result) {
		std::cout << -1;
	}
	else {
		std::cout << result << '\n';
		int curr = 0;
		while (curr != -1) {
			std::cout << curr + 1 << " ";
			curr = nextIndexes[curr];
		}
	}

	delete[] nextIndexes;
	delete[] check;
	delete[] arr;
	return 0;
}