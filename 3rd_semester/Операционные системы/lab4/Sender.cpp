#include <iostream>
#include <string>
#include <Windows.h>

const int MAX_LENGTH = 20;

struct QueueHeader {
    int size;
    int readIndex;
    int writeIndex;
    int count;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: Sender.exe <filename> <senderId>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int senderId = std::stoi(argv[2]);
    int processId = GetCurrentProcessId();

    // 1. Открыть файл для передачи сообщений
    HANDLE hFile = CreateFileA(
        filename.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Sender " << senderId << ": Error opening file " << filename << std::endl;
        return 1;
    }

    // Открываем объекты синхронизации
    HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, "QueueMutex");
    HANDLE hEmptySemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "EmptySemaphore");
    HANDLE hFullSemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "FullSemaphore");

    // 2. Отправить процессу Receiver сигнал на готовность к работе
    std::string readyEventName = "SenderReady_" + std::to_string(senderId);
    HANDLE hSenderReady = OpenEventA(EVENT_ALL_ACCESS, FALSE, readyEventName.c_str());
    if (hSenderReady) {
        SetEvent(hSenderReady);
        CloseHandle(hSenderReady);
        std::cout << "Sender " << senderId << " (PID: " << processId << ") is ready!" << std::endl;
    }
    else {
        std::cout << "Sender " << senderId << " ERROR: Cannot open ready event!" << std::endl;
    }

    // 3. Циклическое выполнение действий
    char choice;

    do {
        std::cout << "\nSender " << senderId << " Menu (PID: " << processId << "):\n";
        std::cout << "1. Send message to Receiver\n";
        std::cout << "2. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == '1') {
            std::string message;
            std::cout << "Enter message (max " << MAX_LENGTH - 1 << " chars): ";
            std::cin.ignore();
            std::getline(std::cin, message);

            if (message.length() >= MAX_LENGTH) {
                message = message.substr(0, MAX_LENGTH - 1);
            }

            // Ожидаем свободного места в очереди
            DWORD result = WaitForSingleObject(hEmptySemaphore, 0);
            if (result == WAIT_OBJECT_0) {
                WaitForSingleObject(hMutex, INFINITE);

                // Читаем текущий заголовок
                QueueHeader currentHeader;
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                DWORD bytesRead;
                ReadFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesRead, NULL);

                if (currentHeader.count < currentHeader.size) {
                    // Записываем сообщение
                    LARGE_INTEGER offset;
                    offset.QuadPart = sizeof(QueueHeader) + currentHeader.writeIndex * MAX_LENGTH;
                    SetFilePointer(hFile, offset.LowPart, &offset.HighPart, FILE_BEGIN);
                    DWORD bytesWritten;
                    WriteFile(hFile, message.c_str(), message.length() + 1, &bytesWritten, NULL);

                    // Обновляем заголовок
                    currentHeader.writeIndex = (currentHeader.writeIndex + 1) % currentHeader.size;
                    currentHeader.count++;

                    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                    WriteFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesWritten, NULL);

                    std::cout << "Message sent: " << message << std::endl;

                    // Сигнализируем о новом сообщении
                    ReleaseSemaphore(hFullSemaphore, 1, NULL);
                }

                ReleaseMutex(hMutex);
            }
            else {
                std::cout << "Queue is full. Waiting for free space..." << std::endl;
                WaitForSingleObject(hEmptySemaphore, INFINITE);

                // Повторяем запись после получения места
                WaitForSingleObject(hMutex, INFINITE);

                QueueHeader currentHeader;
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                DWORD bytesRead;
                ReadFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesRead, NULL);

                if (currentHeader.count < currentHeader.size) {
                    LARGE_INTEGER offset;
                    offset.QuadPart = sizeof(QueueHeader) + currentHeader.writeIndex * MAX_LENGTH;
                    SetFilePointer(hFile, offset.LowPart, &offset.HighPart, FILE_BEGIN);
                    DWORD bytesWritten;
                    WriteFile(hFile, message.c_str(), message.length() + 1, &bytesWritten, NULL);

                    currentHeader.writeIndex = (currentHeader.writeIndex + 1) % currentHeader.size;
                    currentHeader.count++;

                    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                    WriteFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesWritten, NULL);

                    std::cout << "Message sent: " << message << std::endl;

                    ReleaseSemaphore(hFullSemaphore, 1, NULL);
                }

                ReleaseMutex(hMutex);
            }
        }
    } while (choice != '2');

    // Завершение работы
    CloseHandle(hMutex);
    CloseHandle(hEmptySemaphore);
    CloseHandle(hFullSemaphore);
    CloseHandle(hFile);

    return 0;
}