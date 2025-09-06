#include "employee.h"
#include <iostream>
#include <Windows.h>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Program usage: Creator <binary_file> <record_count>\n";
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

    if (INVALID_HANDLE_VALUE == hOutputFile) {
        std::cerr << "Error creating file: " << GetLastError() << '\n';
        std::cerr << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    for (DWORD i = 0; i < recordsNumber; i++) {
        employee e;
        if (!inputEmployeeData(e, i + 1)) {
            std::cerr << "Error inputting employee data!\n";
            CloseHandle(hOutputFile);
            return 1;
        }

        DWORD bytesWritten;
        WriteFile(
            hOutputFile,
            &e,
            sizeof(employee),
            &bytesWritten,
            NULL
        );

        if (bytesWritten != sizeof(employee)) {
            std::cerr << "Error writing to file\n";
            CloseHandle(hOutputFile);
            std::cerr << "Press Enter to exit...";
            std::cin.get();
            return 1;
        }
    }

    CloseHandle(hOutputFile);
    std::cout << "File created successfully: " << outputFilename << '\n';
    return 0;
}