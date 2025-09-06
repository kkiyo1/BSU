#include "employee.h"
#include <Windows.h>
#include <iostream>
#include <string>

int main() {
    if (GetFileAttributesA("Creator.exe") == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Creator.exe not found! Compiling projects first..." << std::endl;
        std::cout << "Please build all projects in Visual Studio first!" << std::endl;
        system("pause");
        return 1;
    }

    // Проверяем существование Reporter.exe
    if (GetFileAttributesA("Reporter.exe") == INVALID_FILE_ATTRIBUTES) {
        std::cout << "Reporter.exe not found!" << std::endl;
        system("pause");
        return 1;
    }
    char filenameBuffer[256];
    std::cout << "Enter binary filename: ";
    std::cin.getline(filenameBuffer, 256);

    DWORD recordsCount;
    std::cout << "Enter number of records: ";
    std::cin >> recordsCount;
    std::cin.ignore();

    std::string cmdCreator = "Creator.exe " + std::string(filenameBuffer) + " " + std::to_string(recordsCount);
    std::cout << "Creator.exe started..." << '\n';

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(
        NULL,
        const_cast<LPSTR>(cmdCreator.c_str()),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "CreateProcess failed for Creator: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for Creator to finish..." << std::endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printBinaryFile(filenameBuffer);

    char reportFilenameBuffer[256];
    std::cout << "Enter report filename: ";
    std::cin.getline(reportFilenameBuffer, 256);

    LONGLONG hourlyPayment;
    std::cout << "Enter hourly payment: ";
    std::cin >> hourlyPayment;
    std::cin.ignore();

    std::string reporterCmd = "Reporter.exe " + std::string(filenameBuffer) + " " + std::string(reportFilenameBuffer) + " " + std::to_string(hourlyPayment);

    STARTUPINFOA siReporter;
    PROCESS_INFORMATION piReporter;

    ZeroMemory(&siReporter, sizeof(siReporter));
    siReporter.cb = sizeof(siReporter);
    ZeroMemory(&piReporter, sizeof(piReporter));

    if (!CreateProcessA(
        NULL,
        const_cast<LPSTR>(reporterCmd.c_str()),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &siReporter,
        &piReporter
    )) {
        std::cerr << "CreateProcess failed for Reporter: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for Reporter to finish..." << std::endl;
    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hProcess);
    CloseHandle(piReporter.hThread);

    printTextFile(reportFilenameBuffer);

    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}