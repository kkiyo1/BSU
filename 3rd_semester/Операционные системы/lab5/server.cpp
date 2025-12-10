#define _CRT_SECURE_NO_WARNINGS
#include "C:\Users\user\Desktop\osLabs\lab5\include\header.h"
#include <vector>
class EmployeeServer {
private:
    std::string filename;
    HANDLE hPipe;
    HANDLE fileMutex;
    HANDLE hClientProcess;

public:
    EmployeeServer() : hClientProcess(NULL) {
        fileMutex = CreateMutex(NULL, FALSE, NULL);
    }

    ~EmployeeServer() {
        CloseHandle(fileMutex);
        if (hClientProcess) {
            CloseHandle(hClientProcess);
        }
    }

    void createFile() {
        std::cout << "Введите имя файла: ";
        std::cin >> filename;

        int n;
        std::cout << "Введите количество сотрудников: ";
        std::cin >> n;

        std::vector<employee> employees;
        for (int i = 0; i < n; i++) {
            employee emp;
            std::cout << "\nСотрудник " << (i + 1) << ":\n";
            std::cout << "  ID: ";
            std::cin >> emp.num;
            std::cout << "  Имя: ";
            std::cin >> emp.name;
            std::cout << "  Часы: ";
            std::cin >> emp.hours;

            employees.push_back(emp);
        }

        saveToFile(employees);
        std::cout << "\nФайл создан успешно.\n";
    }

    void saveToFile(const std::vector<employee>& employees) {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            for (const auto& emp : employees) {
                file.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
            }
            file.close();
        }
    }

    std::vector<employee> loadFromFile() {
        std::vector<employee> employees;
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            employee emp;
            while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
                employees.push_back(emp);
            }
            file.close();
        }
        return employees;
    }

    void printFile() {
        std::cout << "\n=== СОДЕРЖИМОЕ ФАЙЛА ===\n";
        auto employees = loadFromFile();
        for (const auto& emp : employees) {
            emp.print();
        }
        std::cout << "=======================\n";
    }

    void launchClient() {
        std::cout << "\nЗапуск клиента...\n";

        STARTUPINFO si = { 0 };
        PROCESS_INFORMATION pi = { 0 };
        si.cb = sizeof(si);

        std::wstring commandLine = L"client.exe";

        if (CreateProcess(
            NULL,
            &commandLine[0],
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si,
            &pi
        )) {
            hClientProcess = pi.hProcess;
            CloseHandle(pi.hThread);
        }
        else {
            std::cerr << "Не удалось запустить клиент.\n";
        }
        Sleep(2000);
    }

    void startServer() {
        createFile();
        printFile();
        launchClient();

        hPipe = CreateNamedPipe(
            PIPE_NAME,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            1,
            BUFFER_SIZE,
            BUFFER_SIZE,
            0,
            NULL
        );

        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Ошибка создания канала: " << GetLastError() << std::endl;
            return;
        }

        std::cout << "\nСервер запущен. Ожидание подключения клиента...\n";
        std::cout << "Канал: " << std::string(PIPE_NAME, PIPE_NAME + wcslen(PIPE_NAME)) << "\n";

        if (ConnectNamedPipe(hPipe, NULL)) {
            std::cout << "Клиент подключен!\n";
            handleClient();
        }
        else {
            DWORD error = GetLastError();
            if (error == ERROR_PIPE_CONNECTED) {
                std::cout << "Клиент уже подключен!\n";
                handleClient();
            }
            else {
                std::cerr << "Ошибка подключения: " << error << std::endl;
            }
        }

        CloseHandle(hPipe);
    }

    void handleClient() {
        ClientRequest request;
        ServerResponse response;
        DWORD bytesRead, bytesWritten;

        while (true) {
            if (!ReadFile(hPipe, &request, sizeof(ClientRequest), &bytesRead, NULL)) {
                DWORD error = GetLastError();
                if (error == ERROR_BROKEN_PIPE) {
                    std::cout << "Клиент отключился.\n";
                }
                else {
                    std::cerr << "Ошибка чтения: " << error << std::endl;
                }
                break;
            }

            if (bytesRead == 0) {
                std::cout << "Клиент закрыл соединение.\n";
                break;
            }

            std::cout << "\n[СЕРВЕР] Получен запрос: ";
            switch (request.operation) {
            case OP_READ:
                std::cout << "ЧТЕНИЕ";
                break;
            case OP_WRITE:
                std::cout << "ЗАПИСЬ";
                break;
            case OP_EXIT:
                std::cout << "ВЫХОД";
                break;
            }
            std::cout << " (ID: " << request.employeeId << ")\n";

            switch (request.operation) {
            case OP_READ:
                handleRead(request, response);
                break;

            case OP_WRITE:
                handleWrite(request, response);
                break;

            case OP_EXIT:
                std::cout << "[СЕРВЕР] Клиент завершил работу.\n";
                return;
            }

            if (!WriteFile(hPipe, &response, sizeof(ServerResponse), &bytesWritten, NULL)) {
                std::cerr << "Ошибка отправки ответа: " << GetLastError() << std::endl;
                break;
            }
        }
    }

    void handleRead(const ClientRequest& request, ServerResponse& response) {
        auto employees = loadFromFile();
        bool found = false;

        for (const auto& emp : employees) {
            if (emp.num == request.employeeId) {
                response.empData = emp;
                found = true;
                break;
            }
        }

        if (found) {
            strcpy(response.message, "Чтение успешно");
            response.success = true;
            std::cout << "[СЕРВЕР] Отправлены данные сотрудника ID: " << request.employeeId << std::endl;
        }
        else {
            strcpy(response.message, "Сотрудник не найден");
            response.success = false;
            std::cout << "[СЕРВЕР] Сотрудник ID: " << request.employeeId << " не найден\n";
        }
    }

    void handleWrite(const ClientRequest& request, ServerResponse& response) {
        WaitForSingleObject(fileMutex, INFINITE);

        auto employees = loadFromFile();
        bool found = false;
        int foundIndex = -1;

        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].num == request.employeeId) {
                foundIndex = i;
                found = true;
                break;
            }
        }

        if (found && foundIndex != -1) {
            response.empData = employees[foundIndex];

            employees[foundIndex] = request.empData;

            saveToFile(employees);
            strcpy(response.message, "Запись успешно обновлена");
            response.success = true;

            std::cout << "[СЕРВЕР] Обновлен сотрудник:\n";
            std::cout << "  Старые данные: ID=" << response.empData.num
                << ", Имя=" << response.empData.name
                << ", Часы=" << response.empData.hours << std::endl;
            std::cout << "  Новые данные: ID=" << request.empData.num
                << ", Имя=" << request.empData.name
                << ", Часы=" << request.empData.hours << std::endl;
        }
        else {
            strcpy(response.message, "Сотрудник не найден");
            response.success = false;
            std::cout << "[СЕРВЕР] Сотрудник ID: " << request.employeeId << " не найден\n";
        }

        ReleaseMutex(fileMutex);
    }

    void waitForClient() {
        if (hClientProcess) {
            std::cout << "\nОжидание завершения клиента...\n";
            WaitForSingleObject(hClientProcess, INFINITE);
            std::cout << "Клиент завершил работу.\n";
        }
    }

    void run() {
        std::cout << "=== СЕРВЕР УПРАВЛЕНИЯ ДОСТУПОМ К ФАЙЛУ ===\n\n";
        startServer();
        waitForClient();
        std::cout << "\n=== ФИНАЛЬНОЕ СОДЕРЖИМОЕ ФАЙЛА ===\n";
        printFile();

        std::cout << "\nНажмите Enter для выхода...";
        std::cin.ignore();
        std::cin.get();
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    EmployeeServer server;
    server.run();

    return 0;
}