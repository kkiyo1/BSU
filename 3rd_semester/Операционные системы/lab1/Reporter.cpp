#include "employee.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Program usage: Reporter <input_file> <output_file> <hourly_rate>\n";
        return 1;
    }

    LPCSTR inputFilename = argv[1];
    LPCSTR outputFilename = argv[2];
    double hourlyPayment = std::stod(argv[3]);

    HANDLE hInputFile = CreateFileA(
        inputFilename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (INVALID_HANDLE_VALUE == hInputFile) {
        std::cerr << "Cannot open file " << inputFilename << '\n';
        return 1;
    }

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
        std::cerr << "Cannot create file " << outputFilename << '\n';
        CloseHandle(hInputFile);
        return 1;
    }

    std::stringstream report;
    report << "Report for file: " << inputFilename << '\n';
    report << "==========================================\n";
    report << std::setw(8) << "Number" << std::setw(12) << "Name"
        << std::setw(10) << "Hours" << std::setw(12) << "Salary" << '\n';
    report << "------------------------------------------\n";

    employee e;
    DWORD bytesRead;
    int totalEmployees = 0;
    double totalSalary = 0;

    while (ReadFile(hInputFile, &e, sizeof(employee), &bytesRead, NULL) && bytesRead == sizeof(employee)) {
        double salary = e.hours * hourlyPayment;
        totalEmployees++;
        totalSalary += salary;

        report << std::setw(8) << e.num
            << std::setw(12) << e.name
            << std::setw(10) << std::fixed << std::setprecision(2) << e.hours
            << std::setw(12) << std::fixed << std::setprecision(2) << salary << '\n';
    }

    report << "==========================================\n";
    report << "Total employees: " << std::setw(3) << totalEmployees << '\n';
    report << "Total salary: $" << std::fixed << std::setprecision(2) << totalSalary << '\n';
    report << "Hourly rate: $" << std::fixed << std::setprecision(2) << hourlyPayment << '\n';

    std::string reportContent = report.str();

    DWORD bytesWritten;
    WriteFile(
        hOutputFile,
        reportContent.c_str(),
        reportContent.size(),
        &bytesWritten,
        NULL
    );

    CloseHandle(hInputFile);
    CloseHandle(hOutputFile);

    std::cout << "Report created successfully: " << outputFilename << '\n';
    return 0;
}