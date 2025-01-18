#pragma once
#include "process_monitor/Interfaces.hpp"
#include <memory>
#include <thread>
#include <atomic>

namespace procmon {
    class SystemMonitor {
    public:
        SystemMonitor();
        ~SystemMonitor();

        void start();
        void stop();
        void setCollectionInterval(std::chrono::milliseconds interval);
        
        void addMetricsCollector(std::shared_ptr<IMetricsCollector> collector);
        void addDataLogger(std::shared_ptr<IDataLogger> logger);

    private:
        void monitoringLoop();
        
        std::vector<std::shared_ptr<IMetricsCollector>> collectors_;
        std::vector<std::shared_ptr<IDataLogger>> loggers_;
        std::chrono::milliseconds interval_;
        std::thread monitorThread_;
        std::atomic<bool> running_;
    };
}