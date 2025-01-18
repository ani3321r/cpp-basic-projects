#pragma once
#include "process_monitor/Interfaces.hpp"
#include <mutex>
#include <deque>
#include <fstream>
#include <filesystem>

namespace procmon {
    class DataLogger : public IDataLogger {
    public:
        DataLogger(const std::filesystem::path& logDir, size_t maxMemoryEntries = 3600);
        ~DataLogger();

        void logSystemMetrics(const SystemMetrics& metrics) override;
        void logProcessMetrics(const std::vector<ProcessInfo>& processes) override;
        
        std::vector<SystemMetrics> getSystemMetricsHistory(
            std::chrono::system_clock::time_point start,
            std::chrono::system_clock::time_point end) override;

    private:
        void rotateLogFiles();
        void writeMetricsToFile(const SystemMetrics& metrics);
        void writeProcessesToFile(const std::vector<ProcessInfo>& processes);

        std::filesystem::path logDir_;
        std::filesystem::path currentSystemLogFile_;
        std::filesystem::path currentProcessLogFile_;
        
        std::deque<SystemMetrics> memoryMetrics_;
        size_t maxMemoryEntries_;
        
        std::mutex metricsMutex_;
        std::mutex fileMutex_;
        
        std::ofstream systemLogStream_;
        std::ofstream processLogStream_;
    };
}