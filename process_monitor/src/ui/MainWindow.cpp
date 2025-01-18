#include "ui/MainWindow.hpp"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "utils/FormatUtils.hpp"
#include <d3d11.h>

namespace procmon {
    MainWindow::MainWindow(std::shared_ptr<IMetricsCollector> collector,
                         std::shared_ptr<IDataLogger> logger)
        : collector_(collector)
        , logger_(logger)
        , processTable_(std::make_unique<ProcessTable>())
        , metricsGraph_(std::make_unique<MetricsGraph>())
        , shouldClose_(false) {
    }

    void MainWindow::render() {
        updateMetrics();
        
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Process Monitor", nullptr, 
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        renderMainMenuBar();
        renderSystemOverview();

        // Render process table and graphs in a split layout
        ImGui::Columns(2, "split", true);
        
        // Left column: Process table
        ImGui::BeginChild("Processes");
        processTable_->render(currentProcesses_);
        ImGui::EndChild();
        ImGui::NextColumn();
        
        // Right column: Graphs
        ImGui::BeginChild("Graphs");
        metricsGraph_->render(currentMetrics_);
        ImGui::EndChild();
        
        ImGui::Columns(1);
        ImGui::End();
    }

    void MainWindow::renderMainMenuBar() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    shouldClose_ = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Show System Overview", nullptr, &showSystemOverview_);
                ImGui::MenuItem("Show Graphs", nullptr, &showGraphs_);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }

    void MainWindow::renderSystemOverview() {
        ImGui::BeginChild("Overview", ImVec2(0, 120), true);
        
        // CPU Usage
        ImGui::Text("CPU Usage");
        ImGui::ProgressBar(currentMetrics_.cpu_total / 100.0f, 
            ImVec2(-1, 0), 
            FormatUtils::formatPercentage(currentMetrics_.cpu_total).c_str());

        // Memory Usage
        ImGui::Text("Memory Usage");
        float memoryPercentage = currentMetrics_.memory_used / currentMetrics_.memory_total;
        ImGui::ProgressBar(memoryPercentage, ImVec2(-1, 0),
            FormatUtils::formatBytes(currentMetrics_.memory_used).c_str());

        // Disk I/O
        ImGui::Text("Disk I/O: Read %s/s, Write %s/s",
            FormatUtils::formatBytes(currentMetrics_.disk_read_bytes).c_str(),
            FormatUtils::formatBytes(currentMetrics_.disk_write_bytes).c_str());

        // Network I/O
        ImGui::Text("Network: In %s/s, Out %s/s",
            FormatUtils::formatBytes(currentMetrics_.network_in_bytes).c_str(),
            FormatUtils::formatBytes(currentMetrics_.network_out_bytes).c_str());

        ImGui::EndChild();
    }

    void MainWindow::updateMetrics() {
        currentMetrics_ = collector_->collectSystemMetrics();
        currentProcesses_ = collector_->collectProcessMetrics();
    }

    bool MainWindow::shouldClose() const {
        return shouldClose_;
    }
}