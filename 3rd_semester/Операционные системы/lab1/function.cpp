#include "employee.h"
#include <iostream>
#include <Windows.h>
#include <string>

void printBinaryFile(const char* filename) {
    HANDLE hFile = CreateFileA(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (INVALID_HANDLE_VALUE == hFile ) {
        std::cout << "Cannot open file for reading: " << filename << '\n';
        return;
    }

    std::cout << "Number\tName\tHours\n";

    employee emp;
    DWORD bytesRead;

    while (ReadFile(hFile, &emp, sizeof(employee), &bytesRead, NULL) && bytesRead == sizeof(employee)) {
        std::cout << emp.num << '\t' << emp.name << '\t' << emp.hours << '\n';
    }

    CloseHandle(hFile);
}

void printTextFile(const char* filename) {
    HANDLE hFile = CreateFileA(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (INVALID_HANDLE_VALUE == hFile) {
        std::cout << "Cannot open report file: " << filename << '\n';
        return;
    }

    std::cout << "\nReport content:\n";

    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    while (ReadFile(hFile, buffer, BUFFER_SIZE - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << buffer;
    }

    CloseHandle(hFile);
}

bool isNumber(const char* str) {
    if ('-' == str[0]) return true;
    for (int i = 0; str[i]; i++) {
        if (!std::isdigit(str[i])) return false;
    }
    return true;
}

bool inputEmployeeData(employee& emp, int employeeNumber) {
    std::cout << "Employee " << employeeNumber << ":\n";

    bool validInput = false;
    do {
        std::cout << "  number: ";
        std::cin >> emp.num;

        if (std::cin.fail() || emp.num <= 0 || std::floor(emp.num) != emp.num) {
            std::cout << "Error: Please enter a positive integer for number!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    validInput = false;
    do {
        std::cout << "  name: ";
        std::cin >> emp.name;
        if (strlen(emp.name) == 0 || strlen(emp.name) >= 20 || isNumber(emp.name)) {
            std::cout << "Error: Please enter a valid name\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    validInput = false;
    do {
        std::cout << "  hours: ";
        std::cin >> emp.hours;

        if (std::cin.fail() || emp.hours < 0 || std::floor(emp.hours) != emp.hours) {
            std::cout << "Error: Please enter a positive integer for hours\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    return true;
}