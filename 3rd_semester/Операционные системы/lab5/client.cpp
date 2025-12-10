#define _CRT_SECURE_NO_WARNINGS

#include "C:\Users\user\Desktop\osLabs\lab5\include\header.h"
class EmployeeClient {
private:
    HANDLE hPipe;

public:
    bool connectToServer() {
        std::cout << "Подключение к серверу...\n";
        for (int i = 0; i < 10; i++) {
            hPipe = CreateFile(
                PIPE_NAME,
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL
            );

            if (hPipe != INVALID_HANDLE_VALUE) {
                std::cout << "Подключено!\n";
                return true;
            }

            std::cout << ".";
            Sleep(1000);
        }

        std::cout << "\nОшибка: сервер не найден!\n";
        return false;
    }

    void sendRequest(ClientRequest& request, ServerResponse& response) {
        DWORD bytesWritten, bytesRead;

        WriteFile(hPipe, &request, sizeof(ClientRequest), &bytesWritten, NULL);
        ReadFile(hPipe, &response, sizeof(ServerResponse), &bytesRead, NULL);
    }

    void readEmployee() {
        ClientRequest request;
        ServerResponse response;

        std::cout << "\n=== ЧТЕНИЕ ===\n";
        std::cout << "Введите ID сотрудника: ";
        std::cin >> request.employeeId;

        request.operation = OP_READ;
        sendRequest(request, response);

        if (response.success) {
            std::cout << "\nНайдено:\n";
            response.empData.print();
            std::cout << response.message << std::endl;
        }
        else {
            std::cout << "Ошибка: " << response.message << std::endl;
        }

        pause();
    }

    void modifyEmployee() {
        ClientRequest request;
        ServerResponse response;

        std::cout << "\n=== ИЗМЕНЕНИЕ ===\n";
        std::cout << "Введите ID сотрудника: ";
        std::cin >> request.employeeId;
        request.operation = OP_READ;
        sendRequest(request, response);

        if (!response.success) {
            std::cout << "Ошибка: " << response.message << std::endl;
            pause();
            return;
        }

        std::cout << "\nТекущие данные:\n";
        response.empData.print();

        employee newEmp;
        newEmp.num = request.employeeId;

        std::cout << "\nВведите новые данные:\n";
        std::cout << "Имя (" << response.empData.name << "): ";
        std::cin >> newEmp.name;

        std::cout << "Часы (" << response.empData.hours << "): ";
        std::cin >> newEmp.hours;

        request.operation = OP_WRITE;
        request.empData = newEmp;

        sendRequest(request, response);

        if (response.success) {
            std::cout << "\nУспешно обновлено!\n";
            std::cout << "Старые данные: ";
            response.empData.print();
            std::cout << "Новые данные: ";
            newEmp.print();
        }
        else {
            std::cout << "Ошибка: " << response.message << std::endl;
        }

        pause();
    }

    void pause() {
        std::cout << "\nНажмите Enter...";
        std::cin.ignore();
        std::cin.get();
    }

    void run() {
        if (!connectToServer()) {
            pause();
            return;
        }

        int choice;
        bool running = true;

        while (running) {
            system("cls");
            std::cout << "=== КЛИЕНТ ===\n";
            std::cout << "1. Прочитать запись\n";
            std::cout << "2. Изменить запись\n";
            std::cout << "3. Выход\n";
            std::cout << "Выберите: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                readEmployee();
                break;
            case 2:
                modifyEmployee();
                break;
            case 3:
                running = false;
                break;
            }
        }

        ClientRequest request;
        ServerResponse response;
        request.operation = OP_EXIT;
        sendRequest(request, response);

        CloseHandle(hPipe);
        std::cout << "Клиент завершен.\n";
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    EmployeeClient client;
    client.run();

    return 0;
}