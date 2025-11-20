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

int main() {
    // 1. Ввести с консоли имя бинарного файла и количество записей
    std::string filename;
    int notesCount;

    std::cout << "Enter filename (.bin): ";
    std::cin >> filename;
    std::cout << "Enter number of notes: ";
    std::cin >> notesCount;

    // 2. Создать бинарный файл для сообщений
    HANDLE hFile = CreateFileA(
        filename.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Error creating file\n";
        return 1;
    }

    // Инициализируем заголовок очереди
    QueueHeader header = { notesCount, 0, 0, 0 };
    DWORD bytesWritten;
    WriteFile(hFile, &header, sizeof(QueueHeader), &bytesWritten, NULL);

    // Инициализируем сообщения
    char emptyBuffer[MAX_LENGTH] = { 0 };
    for (int i = 0; i < notesCount; i++) {
        WriteFile(hFile, emptyBuffer, MAX_LENGTH, &bytesWritten, NULL);
    }

    // Создаем объекты синхронизации
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "QueueMutex");
    HANDLE hEmptySemaphore = CreateSemaphoreA(NULL, notesCount, notesCount, "EmptySemaphore");
    HANDLE hFullSemaphore = CreateSemaphoreA(NULL, 0, notesCount, "FullSemaphore");

    // 3. Ввести с консоли количество процессов Sender
    int sendersCount;
    std::cout << "Enter number of senders: ";
    std::cin >> sendersCount;

    // Создаем события готовности для каждого Sender (СНАЧАЛА создаем события)
    HANDLE* senderReadyEvents = new HANDLE[sendersCount];
    for (int i = 0; i < sendersCount; i++) {
        std::string eventName = "SenderReady_" + std::to_string(i);
        senderReadyEvents[i] = CreateEventA(NULL, TRUE, FALSE, eventName.c_str());
        std::cout << "Created event: " << eventName << std::endl;
    }

    // 4. Запустить процессы Sender (передаем ID как параметр)
    STARTUPINFOA* si = new STARTUPINFOA[sendersCount];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[sendersCount];

    std::cout << "Starting " << sendersCount << " sender processes..." << std::endl;

    for (int i = 0; i < sendersCount; i++) {
        ZeroMemory(&si[i], sizeof(STARTUPINFOA));
        si[i].cb = sizeof(STARTUPINFOA);
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        // Передаем имя файла и ID сендера
        std::string commandLine = "Sender.exe " + filename + " " + std::to_string(i);

        if (!CreateProcessA(
            NULL,
            (LPSTR)commandLine.c_str(),
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si[i],
            &pi[i]
        )) {
            std::cout << "Error creating Sender process " << i << std::endl;
        }
        else {
            std::cout << "Sender process " << i << " started successfully!" << std::endl;
        }
    }

    // 5. Ждать сигнал на готовность от всех процессов Sender
    std::cout << "Waiting for all senders to be ready..." << std::endl;
    WaitForMultipleObjects(sendersCount, senderReadyEvents, TRUE, INFINITE);
    std::cout << "All senders are ready!" << std::endl;

    // 6. Циклическое выполнение действий
    char choice;

    do {
        std::cout << "\nReceiver Menu:\n";
        std::cout << "1. Read message from binary file\n";
        std::cout << "2. End task\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == '1') {
            // Ожидаем доступных сообщений
            DWORD result = WaitForSingleObject(hFullSemaphore, 0);
            if (result == WAIT_OBJECT_0) {
                WaitForSingleObject(hMutex, INFINITE);

                // Читаем заголовок
                QueueHeader currentHeader;
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                DWORD bytesRead;
                ReadFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesRead, NULL);

                if (currentHeader.count > 0) {
                    // Читаем сообщение
                    char message[MAX_LENGTH];
                    LARGE_INTEGER offset;
                    offset.QuadPart = sizeof(QueueHeader) + currentHeader.readIndex * MAX_LENGTH;
                    SetFilePointer(hFile, offset.LowPart, &offset.HighPart, FILE_BEGIN);
                    ReadFile(hFile, message, MAX_LENGTH, &bytesRead, NULL);

                    std::cout << "Message received: " << message << std::endl;

                    // Обновляем заголовок
                    currentHeader.readIndex = (currentHeader.readIndex + 1) % currentHeader.size;
                    currentHeader.count--;

                    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                    WriteFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesWritten, NULL);

                    // Освобождаем слот
                    ReleaseSemaphore(hEmptySemaphore, 1, NULL);
                }

                ReleaseMutex(hMutex);
            }
            else {
                std::cout << "No messages available. Waiting for new messages..." << std::endl;
                WaitForSingleObject(hFullSemaphore, INFINITE);

                // Повторяем чтение после получения сигнала
                WaitForSingleObject(hMutex, INFINITE);

                QueueHeader currentHeader;
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                DWORD bytesRead;
                ReadFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesRead, NULL);

                if (currentHeader.count > 0) {
                    char message[MAX_LENGTH];
                    LARGE_INTEGER offset;
                    offset.QuadPart = sizeof(QueueHeader) + currentHeader.readIndex * MAX_LENGTH;
                    SetFilePointer(hFile, offset.LowPart, &offset.HighPart, FILE_BEGIN);
                    ReadFile(hFile, message, MAX_LENGTH, &bytesRead, NULL);

                    std::cout << "Message received: " << message << std::endl;

                    currentHeader.readIndex = (currentHeader.readIndex + 1) % currentHeader.size;
                    currentHeader.count--;

                    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                    WriteFile(hFile, &currentHeader, sizeof(QueueHeader), &bytesWritten, NULL);

                    ReleaseSemaphore(hEmptySemaphore, 1, NULL);
                }

                ReleaseMutex(hMutex);
            }
        }
    } while (choice != '2');

    // Завершение работы
    std::cout << "Shutting down..." << std::endl;

    // Закрываем все handles
    for (int i = 0; i < sendersCount; i++) {
        if (pi[i].hProcess) {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hThread);
            CloseHandle(pi[i].hProcess);
        }
        CloseHandle(senderReadyEvents[i]);
    }

    CloseHandle(hMutex);
    CloseHandle(hEmptySemaphore);
    CloseHandle(hFullSemaphore);
    CloseHandle(hFile);

    delete[] senderReadyEvents;
    delete[] pi;
    delete[] si;

    return 0;
}