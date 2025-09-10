#include <iostream>

int main() {
	int n;
	std::cin >> n;
	int* nums = new int[n];
	for (int i = 0; i < n; i++) std::cin >> nums[i];
	int k;
	std::cin >> k;
	int* targets = new int[k];
	for (int i = 0; i < k;i++) std::cin >> targets[i];

	for (int i = 0; i < k; i++) {
		int l = n, r = n;
		int left = 0;
		int right = n - 1;

		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] >= targets[i]) {
				l = mid;
				right = mid - 1;
			}
			else left = mid + 1;
		}

		left = 0;
		right = n - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] > targets[i]) {
				r = mid;
				right = mid - 1;
			}
			else left = mid + 1;
		}

		bool b = (l<n && targets[i] == nums[l]);
		std::cout << b << " " << l << " " << r << '\n';
	}

	delete[] targets;
	delete[] nums;
	return 0;
}