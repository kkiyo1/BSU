#include "employee.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>

int main() {
    std::cout << "===========================================================================\n";
    char filenameBuffer[256];
    BOOL validExtension = false;
    do {
        std::cout << "Enter binary filename (.bin extension): ";
        std::cin.getline(filenameBuffer, 256);

        size_t len = strlen(filenameBuffer);
        if (len > 4) {
            std::string extension(filenameBuffer + len - 4);
            if (".bin" == extension) {
                validExtension = true;
            }
            else {
                std::cout << "Error: Filename must end with .bin\n";
            }
        }
        else {
            std::cout << "Error: Filename too short\n";
        }
    } while (!validExtension);

    double recordsCount = 0;
    BOOL validNumber = false;

    do {
        std::cout << "Enter number of records (positive number): ";
        std::cin >> recordsCount;

        if (std::cin.fail() || recordsCount <= 0 || std::floor(recordsCount) != recordsCount) {
            std::cout << "Error: Please enter a positive number!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            validNumber = true;
        }
    } while (!validNumber);

    std::cin.ignore();

    std::string cmdCreator = "Creator.exe " + std::string(filenameBuffer) + " " + std::to_string(recordsCount);
    std::cout << "Creator.exe started...\n";

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
        std::cerr << "CreateProcess failed for Creator: " << GetLastError() << '\n';
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printBinaryFile(filenameBuffer);

    char reportFilenameBuffer[256];
    validExtension = false;
    do {
        std::cout << "Enter report filename (.txt extension): ";
        std::cin.getline(reportFilenameBuffer, 256);

        size_t len = strlen(reportFilenameBuffer);
        if (len > 4) {
            std::string extension(reportFilenameBuffer + len - 4);
            if (".txt" == extension) {
                validExtension = true;
            }
            else {
                std::cout << "Error: Filename must end with .txt\n";
            }
        }
        else {
            std::cout << "Error: Filename too short\n";
        }
    } while (!validExtension);

    double hourlyPayment = 0;
    validNumber = false;

    do {
        std::cout << "Enter hourly payment (positive number): ";
        std::cin >> hourlyPayment;

        if (std::cin.fail() || hourlyPayment <= 0) {
            std::cout << "Error: Please enter a positive number!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else {
            validNumber = true;
        }
    } while (!validNumber);

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
        std::cerr << "CreateProcess failed for Reporter: " << GetLastError() << '\n';
        return 1;
    }

    std::cout << "Waiting for Reporter to finish...\n";
    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hProcess);
    CloseHandle(piReporter.hThread);

    printTextFile(reportFilenameBuffer);

    std::cout << "\nProgram completed successfully!\n";
    std::cout << "===========================================================================" << '\n';
    return 0;
}