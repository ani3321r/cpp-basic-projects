#pragma once
#include "process_monitor/Types.hpp"
#include <deque>

namespace procmon {
    class MetricsGraph {
    public:
        MetricsGraph(size_t historySize = 120);
        void render(const SystemMetrics& metrics);

    private:
        void updateHistory(const SystemMetrics& metrics);
        void renderCPUGraph();
        void renderMemoryGraph();
        void renderDiskGraph();
        void renderNetworkGraph();

        std::deque<float> cpuHistory_;
        std::deque<float> memoryHistory_;
        std::deque<float> diskReadHistory_;
        std::deque<float> diskWriteHistory_;
        std::deque<float> networkInHistory_;
        std::deque<float> networkOutHistory_;
        size_t historySize_;
    };
}