#pragma once
#include "process_monitor/Interfaces.hpp"
#include "windows/WindowsPerformanceMonitor.hpp"
#include <memory>

namespace procmon {
    class MetricsCollector : public IMetricsCollector {
    public:
        MetricsCollector();
        SystemMetrics collectSystemMetrics() override;
        std::vector<ProcessInfo> collectProcessMetrics() override;

    private:
        std::unique_ptr<WindowsPerformanceMonitor> perfMonitor_;
        std::chrono::system_clock::time_point lastCollection_;
    };
}