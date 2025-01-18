#pragma once
#include <string>
#include <vector>
#include <chrono>

namespace procmon {
    struct ProcessInfo {
        uint32_t pid;
        std::wstring name;
        double cpu_usage;
        size_t memory_usage;
        size_t virtual_memory;
        uint32_t thread_count;
        uint32_t handle_count;
        std::wstring status;
        std::chrono::system_clock::time_point timestamp;
    };

    struct SystemMetrics {
        double cpu_total;
        double memory_used;
        double memory_total;
        double disk_read_bytes;
        double disk_write_bytes;
        double network_in_bytes;
        double network_out_bytes;
        std::chrono::system_clock::time_point timestamp;
    };
}