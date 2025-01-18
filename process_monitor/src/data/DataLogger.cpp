#include "data/DataLogger.hpp"
#include "utils/TimeUtils.hpp"
#include "utils/StringUtils.hpp"
#include <sstream>

namespace procmon {
    DataLogger::DataLogger(const std::filesystem::path& logDir, size_t maxMemoryEntries)
        : logDir_(logDir)
        , maxMemoryEntries_(maxMemoryEntries) {
        std::filesystem::create_directories(logDir_);
        rotateLogFiles();
    }

    DataLogger::~DataLogger() {
        std::lock_guard<std::mutex> fileGuard(fileMutex_);
        if (systemLogStream_.is_open()) systemLogStream_.close();
        if (processLogStream_.is_open()) processLogStream_.close();
    }

    void DataLogger::logSystemMetrics(const SystemMetrics& metrics) {
        {
            std::lock_guard<std::mutex> metricsGuard(metricsMutex_);
            memoryMetrics_.push_back(metrics);
            while (memoryMetrics_.size() > maxMemoryEntries_) {
                memoryMetrics_.pop_front();
            }
        }
        
        writeMetricsToFile(metrics);
    }

    void DataLogger::logProcessMetrics(const std::vector<ProcessInfo>& processes) {
        writeProcessesToFile(processes);
    }

    std::vector<SystemMetrics> DataLogger::getSystemMetricsHistory(
        std::chrono::system_clock::time_point start,
        std::chrono::system_clock::time_point end) {
        std::lock_guard<std::mutex> metricsGuard(metricsMutex_);
        std::vector<SystemMetrics> result;
        
        for (const auto& metric : memoryMetrics_) {
            if (metric.timestamp >= start && metric.timestamp <= end) {
                result.push_back(metric);
            }
        }
        
        return result;
    }

    void DataLogger::rotateLogFiles() {
        auto timestamp = TimeUtils::getTimestampString();
        
        currentSystemLogFile_ = logDir_ / ("system_" + timestamp + ".log");
        currentProcessLogFile_ = logDir_ / ("process_" + timestamp + ".log");
        
        std::lock_guard<std::mutex> fileGuard(fileMutex_);
        if (systemLogStream_.is_open()) systemLogStream_.close();
        if (processLogStream_.is_open()) processLogStream_.close();
        
        systemLogStream_.open(currentSystemLogFile_, std::ios::app);
        processLogStream_.open(currentProcessLogFile_, std::ios::app);
    }

    void DataLogger::writeMetricsToFile(const SystemMetrics& metrics) {
        std::stringstream ss;
        ss << TimeUtils::formatTimestamp(metrics.timestamp) << ","
           << metrics.cpu_total << ","
           << metrics.memory_used << ","
           << metrics.memory_total << ","
           << metrics.disk_read_bytes << ","
           << metrics.disk_write_bytes << ","
           << metrics.network_in_bytes << ","
           << metrics.network_out_bytes << "\n";
        
        std::lock_guard<std::mutex> fileGuard(fileMutex_);
        systemLogStream_ << ss.str();
        systemLogStream_.flush();
    }

    void DataLogger::writeProcessesToFile(const std::vector<ProcessInfo>& processes) {
        std::stringstream ss;
        for (const auto& proc : processes) {
            ss << TimeUtils::formatTimestamp(proc.timestamp) << ","
               << proc.pid << ","
               << StringUtils::wstringToString(proc.name) << ","
               << proc.cpu_usage << ","
               << proc.memory_usage << ","
               << proc.virtual_memory << ","
               << proc.thread_count << ","
               << proc.handle_count << "\n";
        }
        
        std::lock_guard<std::mutex> fileGuard(fileMutex_);
        processLogStream_ << ss.str();
        processLogStream_.flush();
    }
}