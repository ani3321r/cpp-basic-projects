#pragma once
#include <chrono>
#include <string>

namespace procmon {
    class TimeUtils {
    public:
        static std::string getTimestampString() {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            char buffer[26];
            ctime_s(buffer, sizeof(buffer), &time);
            std::string timestamp(buffer);
            timestamp.pop_back(); // Remove newline
            return timestamp;
        }

        static std::string formatTimestamp(std::chrono::system_clock::time_point tp) {
            auto time = std::chrono::system_clock::to_time_t(tp);
            char buffer[26];
            ctime_s(buffer, sizeof(buffer), &time);
            std::string timestamp(buffer);
            timestamp.pop_back(); // Remove newline
            return timestamp;
        }
    };
}