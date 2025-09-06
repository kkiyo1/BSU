#include "employee.h"
#include <iostream>
#include <Windows.h>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <binary_file> <record_count>" << std::endl;
        std::cerr << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    LPCSTR outputFilename = argv[1];
    DWORD recordsNumber = std::stoi(argv[2]);

    HANDLE hOutputFile = CreateFileA(
        outputFilename,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hOutputFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Error creating file: " << GetLastError() << std::endl;
        std::cerr << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    for (DWORD i = 0; i < recordsNumber; i++) {
        employee e;
        std::cout << "Employee " << i + 1 << ":\n";
        std::cout << "  number: ";
        std::cin >> e.num;
        std::cout << "  name: ";
        std::cin >> e.name;
        std::cout << "  hours: ";
        std::cin >> e.hours;

        DWORD bytesWritten;
        WriteFile(
            hOutputFile,
            &e,
            sizeof(employee),
            &bytesWritten,
            NULL
        );

        if (bytesWritten != sizeof(employee)) {
            std::cerr << "Error writing to file" << std::endl;
            CloseHandle(hOutputFile);
            std::cerr << "Press Enter to exit...";
            std::cin.get();
            return 1;
        }
    }

    CloseHandle(hOutputFile);
    std::cout << "File created successfully: " << outputFilename << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}