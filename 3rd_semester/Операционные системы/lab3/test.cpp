#include "pch.h"
#include "header.h"
#include <Windows.h>
#include <thread>
#include <vector>

TEST(MarkerFunctionTest, SingleThreadMarking) {
    n = 10;
    threadCount = 1;
    activeThreads = threadCount;

    arr = new int[n] {};
    InitializeCriticalSection(&cs);

    startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    continueEvents = new HANDLE[threadCount];
    stopEvents = new HANDLE[threadCount];
    threadStoppedEvents = new HANDLE[threadCount];

    for (int i = 0; i < threadCount; i++) {
        continueEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        stopEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        threadStoppedEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    int* threadIdPtr = new int(0);
    SetEvent(startEvent);

    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, marker, threadIdPtr, 0, &threadId);
    EXPECT_NE(hThread, nullptr);

    Sleep(100);

    int markedCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            markedCount++;
        }
    }

    EXPECT_GT(markedCount, 0);

    SetEvent(stopEvents[0]);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    for (int i = 0; i < threadCount; i++) {
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(threadStoppedEvents[i]);
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&cs);

    delete[] arr;
    delete[] threadStoppedEvents;
    delete[] stopEvents;
    delete[] continueEvents;
}

TEST(MarkerFunctionTest, ThreadCleanupOnStop) {
    n = 5;
    threadCount = 1;
    activeThreads = threadCount;

    arr = new int[n] {};
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }

    InitializeCriticalSection(&cs);

    startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    continueEvents = new HANDLE[threadCount];
    stopEvents = new HANDLE[threadCount];
    threadStoppedEvents = new HANDLE[threadCount];

    continueEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    stopEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    threadStoppedEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);

    int* threadIdPtr = new int(0);
    SetEvent(startEvent);

    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, marker, threadIdPtr, 0, &threadId);

    Sleep(50);

    SetEvent(stopEvents[0]);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], 0);
    }

    for (int i = 0; i < threadCount; i++) {
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(threadStoppedEvents[i]);
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&cs);

    delete[] arr;
    delete[] threadStoppedEvents;
    delete[] stopEvents;
    delete[] continueEvents;
}

TEST(MarkerFunctionTest, MultipleThreadsNoConflict) {
    n = 20;
    threadCount = 2;
    activeThreads = threadCount;

    arr = new int[n] {};
    InitializeCriticalSection(&cs);

    startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    continueEvents = new HANDLE[threadCount];
    stopEvents = new HANDLE[threadCount];
    threadStoppedEvents = new HANDLE[threadCount];

    for (int i = 0; i < threadCount; i++) {
        continueEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        stopEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        threadStoppedEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    HANDLE* hThreads = new HANDLE[threadCount];

    for (int i = 0; i < threadCount; i++) {
        int* threadIdPtr = new int(i);
        hThreads[i] = CreateThread(NULL, 0, marker, threadIdPtr, 0, NULL);
        EXPECT_NE(hThreads[i], nullptr);
    }

    SetEvent(startEvent);

    Sleep(100);

    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            int threadValue = arr[i];
            EXPECT_TRUE(threadValue == 1 || threadValue == 2);
        }
    }

    for (int i = 0; i < threadCount; i++) {
        SetEvent(stopEvents[i]);
        WaitForSingleObject(hThreads[i], INFINITE);
        CloseHandle(hThreads[i]);
    }

    for (int i = 0; i < threadCount; i++) {
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(threadStoppedEvents[i]);
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&cs);

    delete[] hThreads;
    delete[] arr;
    delete[] threadStoppedEvents;
    delete[] stopEvents;
    delete[] continueEvents;
}

TEST(MarkerFunctionTest, ThreadStopsOnOccupiedElement) {
    n = 3;
    threadCount = 1;
    activeThreads = threadCount;

    arr = new int[n] {};
    arr[0] = 99;
    arr[1] = 99;
    arr[2] = 99;

    InitializeCriticalSection(&cs);

    startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    continueEvents = new HANDLE[threadCount];
    stopEvents = new HANDLE[threadCount];
    threadStoppedEvents = new HANDLE[threadCount];

    continueEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    stopEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    threadStoppedEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);

    int* threadIdPtr = new int(0);
    SetEvent(startEvent);

    DWORD threadId;
    HANDLE hThread = CreateThread(NULL, 0, marker, threadIdPtr, 0, &threadId);

    Sleep(100);

    DWORD result = WaitForSingleObject(threadStoppedEvents[0], 0);
    EXPECT_EQ(result, WAIT_OBJECT_0);

    SetEvent(continueEvents[0]);
    ResetEvent(continueEvents[0]);

    Sleep(50);

    SetEvent(stopEvents[0]);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    for (int i = 0; i < threadCount; i++) {
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(threadStoppedEvents[i]);
    }
    CloseHandle(startEvent);
    DeleteCriticalSection(&cs);

    delete[] arr;
    delete[] threadStoppedEvents;
    delete[] stopEvents;
    delete[] continueEvents;
}