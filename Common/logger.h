#pragma once
#include <Windows.h>
#include <stdio.h>

//void Log(const char* format, ...);
//void PrintStackTrace(unsigned long dwSize);

/// <summary>
/// Prints to windows debug output.
/// </summary>
extern void Log(const char* format, ...);