#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int countStrings(ifstream& filename) {
	int count = 0;
	string s;
	while (getline(filename, s)) count++;
	filename.clear();
	filename.seekg(0);
	return count;
}

int main() {
	ifstream inputFile("input.txt");
	if (!inputFile) {
		cout << "Error opening file.";
		return 1;
	}

	int n = countStrings(inputFile);
	string* arr = new string[n];

	for (int i = 0; i < n; i++) getline(inputFile, arr[i]);
	
	regex rgx(R"(((25[0-5]|2[0-4][0-9]|1?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|1?[0-9][0-9]?))");

	ofstream outputFile("output.txt");
	if (!outputFile) {
		cout << "Error opening file.";
		return 1;
	}
	for (int i = 0; i < n; i++) {
		if (regex_match(arr[i], rgx)) {
			outputFile << arr[i] << '\n';
			cout << arr[i] << '\n';
		}
	}
	delete[] arr;
	return 0;
}