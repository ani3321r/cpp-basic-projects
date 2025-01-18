#pragma once
#include "process_monitor/Types.hpp"

namespace procmon {
    class ProcessInfoImpl {
    public:
        static ProcessInfo getProcessInfo(uint32_t pid);
        static std::vector<uint32_t> getRunningProcesses();
        static bool isProcessRunning(uint32_t pid);
        static std::wstring getProcessName(uint32_t pid);
        static bool getProcessTimes(uint32_t pid, uint64_t& userTime, uint64_t& kernelTime);
    };
}