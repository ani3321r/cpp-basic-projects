#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace procmon {
    class FormatUtils {
    public:
        static std::string formatBytes(uint64_t bytes) {
            const char* units[] = {"B", "KB", "MB", "GB", "TB"};
            int unitIndex = 0;
            double size = static_cast<double>(bytes);
            
            while (size >= 1024.0 && unitIndex < 4) {
                size /= 1024.0;
                unitIndex++;
            }
            
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << size << " " << units[unitIndex];
            return ss.str();
        }

        static std::string formatPercentage(double value) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << value << "%";
            return ss.str();
        }
    };
}