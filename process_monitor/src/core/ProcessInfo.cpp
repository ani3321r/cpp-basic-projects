#include "core/ProcessInfo.hpp"
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

namespace procmon {
    ProcessInfo ProcessInfoImpl::getProcessInfo(uint32_t pid) {
        ProcessInfo info;
        info.pid = pid;
        info.timestamp = std::chrono::system_clock::now();

        HANDLE processHandle = OpenProcess(
            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE,
            pid
        );

        if (processHandle) {
            // Get process name
            wchar_t processName[MAX_PATH];
            if (GetProcessImageFileNameW(processHandle, processName, MAX_PATH)) {
                info.name = processName;
            }

            // Get memory info
            PROCESS_MEMORY_COUNTERS_EX pmc;
            if (GetProcessMemoryInfo(processHandle, 
                (PROCESS_MEMORY_COUNTERS*)&pmc, 
                sizeof(pmc))) {
                info.memory_usage = pmc.WorkingSetSize;
                info.virtual_memory = pmc.PrivateUsage;
            }

            // Get thread and handle count
            DWORD handleCount;
            if (GetProcessHandleCount(processHandle, &handleCount)) {
                info.handle_count = handleCount;
            }

            CloseHandle(processHandle);
        }

        return info;
    }

    std::vector<uint32_t> ProcessInfoImpl::getRunningProcesses() {
        std::vector<uint32_t> processes;
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        
        if (snapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32W processEntry;
            processEntry.dwSize = sizeof(processEntry);

            if (Process32FirstW(snapshot, &processEntry)) {
                do {
                    processes.push_back(processEntry.th32ProcessID);
                } while (Process32NextW(snapshot, &processEntry));
            }
            CloseHandle(snapshot);
        }
        return processes;
    }

    bool ProcessInfoImpl::isProcessRunning(uint32_t pid) {
        HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
        if (process) {
            DWORD exitCode;
            GetExitCodeProcess(process, &exitCode);
            CloseHandle(process);
            return exitCode == STILL_ACTIVE;
        }
        return false;
    }
}