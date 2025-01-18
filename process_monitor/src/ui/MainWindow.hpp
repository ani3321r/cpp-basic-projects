#pragma once
#include "process_monitor/Interfaces.hpp"
#include "ui/ProcessTable.hpp"
#include "ui/MetricsGraph.hpp"
#include <memory>
#include <vector>

namespace procmon {
    class MainWindow {
    public:
        MainWindow(std::shared_ptr<IMetricsCollector> collector,
                  std::shared_ptr<IDataLogger> logger);
        void render();
        bool shouldClose() const;

    private:
        void renderMainMenuBar();
        void renderSystemOverview();
        void updateMetrics();

        std::shared_ptr<IMetricsCollector> collector_;
        std::shared_ptr<IDataLogger> logger_;
        std::unique_ptr<ProcessTable> processTable_;
        std::unique_ptr<MetricsGraph> metricsGraph_;
        
        SystemMetrics currentMetrics_;
        std::vector<ProcessInfo> currentProcesses_;
        bool shouldClose_;
    };
}