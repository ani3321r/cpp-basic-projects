#include "core/SystemMonitor.hpp"

namespace procmon {
    SystemMonitor::SystemMonitor() 
        : interval_(std::chrono::seconds(1))
        , running_(false) {
    }

    SystemMonitor::~SystemMonitor() {
        stop();
    }

    void SystemMonitor::start() {
        if (!running_) {
            running_ = true;
            monitorThread_ = std::thread(&SystemMonitor::monitoringLoop, this);
        }
    }

    void SystemMonitor::stop() {
        if (running_) {
            running_ = false;
            if (monitorThread_.joinable()) {
                monitorThread_.join();
            }
        }
    }

    void SystemMonitor::setCollectionInterval(std::chrono::milliseconds interval) {
        interval_ = interval;
    }

    void SystemMonitor::addMetricsCollector(std::shared_ptr<IMetricsCollector> collector) {
        collectors_.push_back(collector);
    }

    void SystemMonitor::addDataLogger(std::shared_ptr<IDataLogger> logger) {
        loggers_.push_back(logger);
    }

    void SystemMonitor::monitoringLoop() {
        while (running_) {
            for (auto& collector : collectors_) {
                auto systemMetrics = collector->collectSystemMetrics();
                auto processMetrics = collector->collectProcessMetrics();

                for (auto& logger : loggers_) {
                    logger->logSystemMetrics(systemMetrics);
                    logger->logProcessMetrics(processMetrics);
                }
            }
            
            std::this_thread::sleep_for(interval_);
        }
    }
}