#pragma once

struct employee {
	int num;
	char name[10];
	double hours;
};

void printBinaryFile(const char* filename);
void printTextFile(const char* filename);
bool isNumber(const char* str);
bool inputEmployeeData(employee& emp, int employeeNumber);