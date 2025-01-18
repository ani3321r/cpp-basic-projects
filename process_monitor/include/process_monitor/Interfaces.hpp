#pragma once
#include "Types.hpp"

namespace procmon {
    class IMetricsCollector {
    public:
        virtual ~IMetricsCollector() = default;
        virtual SystemMetrics collectSystemMetrics() = 0;
        virtual std::vector<ProcessInfo> collectProcessMetrics() = 0;
    };

    class IDataLogger {
    public:
        virtual ~IDataLogger() = default;
        virtual void logSystemMetrics(const SystemMetrics& metrics) = 0;
        virtual void logProcessMetrics(const std::vector<ProcessInfo>& processes) = 0;
        virtual std::vector<SystemMetrics> getSystemMetricsHistory(
            std::chrono::system_clock::time_point start,
            std::chrono::system_clock::time_point end) = 0;
    };
}