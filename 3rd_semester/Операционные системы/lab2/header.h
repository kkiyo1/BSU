#pragma once
#include <Windows.h>
#include <vector>

extern DWORD n;
extern std::vector<DWORD> indexes;
extern DWORD average;

void min_max_func(LPVOID lpParam);
void average_func(LPVOID lpParam);