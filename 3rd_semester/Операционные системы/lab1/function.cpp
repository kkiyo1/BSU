#include "employee.h"
#include <string>
#include <Windows.h>
#include <iostream>

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

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }

    std::cout << "Number\tName\tHours" << std::endl;

    employee emp;
    DWORD bytesRead;

    while (ReadFile(hFile, &emp, sizeof(employee), &bytesRead, NULL) && bytesRead == sizeof(employee)) {
        std::cout << emp.num << "\t" << emp.name << "\t" << emp.hours << std::endl;
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

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Cannot open report file: " << filename << std::endl;
        return;
    }

    std::cout << "\nReport content:" << std::endl;

    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;

    while (ReadFile(hFile, buffer, BUFFER_SIZE - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << buffer;
    }

    CloseHandle(hFile);
}