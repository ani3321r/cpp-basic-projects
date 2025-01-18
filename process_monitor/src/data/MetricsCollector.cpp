#include "data/MetricsCollector.hpp"
#include "utils/TimeUtils.hpp"

namespace procmon {
    MetricsCollector::MetricsCollector() 
        : perfMonitor_(std::make_unique<WindowsPerformanceMonitor>()) {
    }

    SystemMetrics MetricsCollector::collectSystemMetrics() {
        auto winMetrics = perfMonitor_->GetSystemMetrics();
        
        SystemMetrics metrics;
        metrics.timestamp = std::chrono::system_clock::now();
        metrics.cpu_total = winMetrics.cpuUsage;
        metrics.memory_used = winMetrics.totalMemoryMB - winMetrics.availableMemoryMB;
        metrics.memory_total = winMetrics.totalMemoryMB;
        metrics.disk_read_bytes = winMetrics.diskReadBytesPerSec;
        metrics.disk_write_bytes = winMetrics.diskWriteBytesPerSec;
        
        return metrics;
    }

    std::vector<ProcessInfo> MetricsCollector::collectProcessMetrics() {
        std::vector<ProcessInfo> processes;
        auto winProcesses = perfMonitor_->GetProcessDetails();
        
        for (const auto& winProc : winProcesses) {
            ProcessInfo proc;
            proc.pid = winProc.pid;
            proc.name = winProc.name;
            proc.cpu_usage = winProc.cpu_percent;
            proc.memory_usage = winProc.workingSetSize;
            proc.virtual_memory = winProc.privateBytes;
            proc.thread_count = winProc.threadCount;
            proc.handle_count = winProc.handleCount;
            proc.timestamp = std::chrono::system_clock::now();
            processes.push_back(proc);
        }
        
        return processes;
    }
}