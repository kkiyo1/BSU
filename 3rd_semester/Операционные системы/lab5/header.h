#ifndef COMMON_H
#define COMMON_H

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#define PIPE_NAME L"\\\\.\\pipe\\EmployeePipe"
#define BUFFER_SIZE 1024

struct employee {
    int num;
    char name[10];
    double hours;

    void print() const {
        std::cout << "ID: " << num
            << ", Name: " << name
            << ", Hours: " << std::fixed << std::setprecision(2) << hours << std::endl;
    }
};

enum OperationType {
    OP_READ = 1,
    OP_WRITE = 2,
    OP_EXIT = 3
};

struct ClientRequest {
    OperationType operation;
    int employeeId;
    employee empData;
};

struct ServerResponse {
    bool success;
    employee empData;
    char message[100];
};

#endif