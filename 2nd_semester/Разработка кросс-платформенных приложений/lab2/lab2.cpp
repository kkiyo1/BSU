#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int stringCount(const string& filename) {
	ifstream inputFile(filename);
	if (!inputFile) cerr << "Error.";
	int i = 0;
	string s;
	while (getline(inputFile, s)) { i++; };
	return i;
}

struct Element1 { //все студенты
	string name;
	string address;
	Element1() {};
	Element1(const string& n, const string& a) : name(n), address(a) {};
	~Element1() {};

	friend ostream& operator<<(ostream& os, const Element1& el) {
		os << el.name << " " << el.address;
		return os;
	}

	friend istream& operator>>(istream& is, Element1& el) {
		cout << "Enter name: ";
		getline(is, el.name);
		cout << "Enter address: ";
		getline(is, el.address);
		return is;
	}

	Element1& operator=(const Element1& el) {
		name = el.name;
		address = el.address;
		return *this;
	}

	bool operator==(const Element1& el) {
		return (name == el.name && address == el.address);
	}

	bool operator>(const Element1& el) {
		return (name > el.name);
	}
};

struct Element2 { //студенты-должники
	string name;
	string address;

	Element2() {};
	Element2(const string& n, const string& a) : name(n), address(a) {};
	~Element2() {};

	friend ostream& operator<<(ostream& os, const Element2& el) {
		os << el.name << " " << el.address;
		return os;
	}

	friend istream& operator>>(istream& is, Element2& el) {
		cout << "Enter name: ";
		getline(is, el.name);
		cout << "Enter address: ";
		getline(is, el.address);
		return is;
	}

	Element2& operator=(const Element2& el) {
		name = el.name;
		address = el.address;
		return *this;
	}

	bool operator==(const Element2& el) {
		return (name == el.name && address == el.address);
	}

	bool operator>(const Element2& el) {
		return (name > el.name);
	}
};

struct Element3 { //студенты сдавшие сессию
	string name;
	string address;

	Element3() {};
	Element3(const string& n, const string& a) : name(n), address(a) {};
	Element3(const Element1& el) : name(el.name), address(el.address) {}
	~Element3() {};

	friend ostream& operator<<(ostream& os, const Element3& el) {
		os << el.name <<  " " << el.address;
		return os;
	}

	friend istream& operator>>(istream& is, Element3& el) {
		cout << "Enter name: ";
		getline(is, el.name);
		cout << "Enter address: ";
		getline(is, el.address);
		return is;
	}

	Element3& operator=(const Element3& el) {
		name = el.name;
		address = el.address;
		return *this;
	}

	Element3& operator=(const Element1& el) {
		name = el.name;
		address = el.address;
		return *this;
	}

	bool operator==(const Element3& el) {
		return (name == el.name && address == el.address);
	}

	bool operator>(const Element3& el) {
		return (name > el.name);
	}
};

template <class T>
class MASSIV {
private:
	int n;
	T* mas;
public:
	MASSIV() {
		mas = NULL;
		n = 0;
	};
	MASSIV(int i) : n(i) { mas = new T[i]; };
	MASSIV(const MASSIV<T>& m) : n(m.n) {
		mas = new T[n];
		for (int i = 0; i < n; i++) {
			mas[i] = m.mas[i];
		}
	}

	~MASSIV() { delete[] mas; };
	

	int getSize() const { return n; }

	/*void print() {
		for (int i = 0; i < n; i++) cout << "Student "<< i+1 << '\n' << mas[i] << '\n';
	}*/

	void readTextData(const string& filename) {
		ifstream inputFile(filename);
		if (!inputFile) {
			cerr << "Error file opening" << endl;
			return;
		}
		int index = 0;
		string line;
		while (getline(inputFile, line) && index < n) {
			size_t pos = line.find('.');
			if (pos != string::npos) {
				string name = line.substr(0, pos);
				string address = line.substr(pos + 1);
				mas[index] = T(name, address);
				index++;
			}
		}
		inputFile.close();
	}

	void writeTextData(const string& filename) {
		ofstream outputFile(filename);
		if (!outputFile) {
			cerr << "Error file opening. ";
		}
		for (int i = 0; i < getSize(); i++) {
			outputFile << mas[i] << '\n';
		}
	}

	void writeBinaryData(const string& filename) {
		ofstream outFile(filename, ios::binary);
		if (!outFile) {
			cerr << "Error file opening. " << filename << '\n';
		}
		outFile.write(reinterpret_cast<const char*>(mas), n * sizeof(int));
		outFile.close();
	}

	void sortByName() {
		for (int i = 0; i < n -1 ; i++) {
			for (int j = 0; j < n - i - 1; j++)
				if (mas[j] > mas[j + 1]) swap(mas[j], mas[j + 1]);
		}
	}

	T& operator[](int index) {
		if (index < 0 || index >= n) {
			throw out_of_range("Out of range");
		}
		return mas[index];
	}

	T& operator[](int index) const {
		if (index < 0 || index >= n) {
			throw out_of_range("Out of range");
		}
		return mas[index];
	}

	friend ostream& operator<<(ostream& os, const MASSIV& arr) {
		for (int i = 0; i < arr.n; i++) {
			os << arr[i] << '\n';
		}
		return os;
	}

	friend istream& operator>>(istream& is, const MASSIV& arr) {
		for (int i = 0; i < arr->getSize(); i++) {
			cin >> mas[i];
		}
	}

	MASSIV<T> substract(MASSIV<T>& arr2) {
		MASSIV<T> arr3(getSize() - arr2.getSize());
		int index = 0;

		for (int i = 0; i < getSize(); i++) {
			bool isFound = false;

			for (int j = 0; j < arr2.getSize(); j++) {
				if (mas[i] == arr2.mas[j]) {
					isFound = true;
					break;
				}
			}

			if (!isFound) {
				arr3[index] = T(mas[i]);
				index++;
			}
		}
		return arr3;
	}
};

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8"); //LC_ALL, "ru_RU.UTF-8"
	MASSIV<int> intMas(3);
	cin >> intMas[0] >> intMas[1] >> intMas[2];
	intMas.sortByName();
	MASSIV<int> intMas2(2);
	cin >> intMas2[0] >> intMas2[1];
	MASSIV<int> intMas3 = intMas.substract(intMas2);
	cout << intMas3;

	MASSIV<Element1> arr1(stringCount("allStudents.txt"));
	arr1.readTextData("allStudents.txt");

	MASSIV<Element1> arr2(stringCount("studentsDebtors.txt"));
	arr2.readTextData("studentsDebtors.txt");
	arr1.sortByName();
	arr2.sortByName();
	//cout << arr1;
	MASSIV<Element1> arr3 = arr1.substract(arr2);
	arr3.sortByName();
	cout << arr3;
	arr3.writeTextData("result.txt");
	arr3.writeBinaryData("binaryResult.txt");
	return 0;
}
