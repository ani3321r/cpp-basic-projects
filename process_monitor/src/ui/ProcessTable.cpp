#include "ui/ProcessTable.hpp"
#include "imgui.h"
#include "utils/FormatUtils.hpp"
#include "utils/StringUtils.hpp"
#include <algorithm>

namespace procmon {
    ProcessTable::ProcessTable()
        : sortColumn_(-1)
        , sortAscending_(true) {
        memset(filterBuffer_, 0, sizeof(filterBuffer_));
    }

    void ProcessTable::render(const std::vector<ProcessInfo>& processes) {
        // Filter input
        ImGui::InputText("Filter", filterBuffer_, sizeof(filterBuffer_));
        
        if (ImGui::BeginTable("ProcessTable", 7, 
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Sortable | 
            ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | 
            ImGuiTableFlags_BordersV | ImGuiTableFlags_RowBg)) {
            
            renderHeader();

            // Filter and sort processes
            std::vector<ProcessInfo> filteredProcesses = processes;
            std::string filter = filterBuffer_;
            if (!filter.empty()) {
                filteredProcesses.erase(
                    std::remove_if(filteredProcesses.begin(), filteredProcesses.end(),
                        [&filter](const ProcessInfo& p) {
                            return StringUtils::wstringToString(p.name).find(filter) == std::string::npos;
                        }), 
                    filteredProcesses.end());
            }

            // Sort if column is selected
            if (sortColumn_ >= 0) {
                std::sort(filteredProcesses.begin(), filteredProcesses.end(),
                    [this](const ProcessInfo& a, const ProcessInfo& b) {
                        bool result = false;
                        switch (sortColumn_) {
                            case 0: result = a.pid < b.pid; break;
                            case 1: result = a.name < b.name; break;
                            case 2: result = a.cpu_usage < b.cpu_usage; break;
                            case 3: result = a.memory_usage < b.memory_usage; break;
                            case 4: result = a.thread_count < b.thread_count; break;
                            case 5: result = a.handle_count < b.handle_count; break;
                        }
                        return sortAscending_ ? result : !result;
                    });
            }

            // Render rows
            for (const auto& process : filteredProcesses) {
                renderRow(process);
            }

            ImGui::EndTable();
        }
    }

    void ProcessTable::renderHeader() {
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_DefaultSort);
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("CPU %");
        ImGui::TableSetupColumn("Memory");
        ImGui::TableSetupColumn("Threads");
        ImGui::TableSetupColumn("Handles");
        ImGui::TableSetupColumn("Status");
        ImGui::TableHeadersRow();

        // Handle sorting
        if (ImGuiTableSortSpecs* sortSpecs = ImGui::TableGetSortSpecs()) {
            if (sortSpecs->SpecsDirty) {
                sortColumn_ = sortSpecs->Specs->ColumnIndex;
                sortAscending_ = sortSpecs->Specs->SortDirection == ImGuiSortDirection_Ascending;
                sortSpecs->SpecsDirty = false;
            }
        }
    }

    void ProcessTable::renderRow(const ProcessInfo& process) {
        ImGui::TableNextRow();
        
        ImGui::TableNextColumn();
        ImGui::Text("%u", process.pid);
        
        ImGui::TableNextColumn();
        ImGui::Text("%s", StringUtils::wstringToString(process.name).c_str());
        
        ImGui::TableNextColumn();
        ImGui::Text("%.1f", process.cpu_usage);
        
        ImGui::TableNextColumn();
        ImGui::Text("%s", FormatUtils::formatBytes(process.memory_usage).c_str());
        
        ImGui::TableNextColumn();
        ImGui::Text("%u", process.thread_count);
        
        ImGui::TableNextColumn();
        ImGui::Text("%u", process.handle_count);
        
        ImGui::TableNextColumn();
        ImGui::Text("%s", StringUtils::wstringToString(process.status).c_str());
    }
}