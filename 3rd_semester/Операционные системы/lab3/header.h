#pragma once
#include <Windows.h>

extern HANDLE startEvent;
extern HANDLE* continueEvents;
extern HANDLE* stopEvents;
extern HANDLE* threadStoppedEvents;
extern int* arr;
extern int n, threadCount, activeThreads;

extern CRITICAL_SECTION cs;

DWORD marker(LPVOID param);