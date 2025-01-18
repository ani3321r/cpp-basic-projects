#pragma once
#include "process_monitor/Types.hpp"
#include <vector>

namespace procmon {
    class ProcessTable {
    public:
        ProcessTable();
        void render(const std::vector<ProcessInfo>& processes);

    private:
        void renderHeader();
        void renderRow(const ProcessInfo& process);
        
        int sortColumn_;
        bool sortAscending_;
        char filterBuffer_[256];
    };
}