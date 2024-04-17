#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <algorithm>
#include <TCHAR.h>
#include <pdh.h>

inline size_t GetCurrentMemoryUsage() {

	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	return pmc.WorkingSetSize >> 20;	//MegaBytes
}
