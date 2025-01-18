#pragma once
#include <string>
#include <windows.h>

namespace procmon {
    class StringUtils {
    public:
        static std::string wstringToString(const std::wstring& wstr) {
            if (wstr.empty()) return std::string();
            int size = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                                         NULL, 0, NULL, NULL);
            std::string result(size, 0);
            WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                              &result[0], size, NULL, NULL);
            return result;
        }

        static std::wstring stringToWString(const std::string& str) {
            if (str.empty()) return std::wstring();
            int size = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(),
                                         NULL, 0);
            std::wstring result(size, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(),
                              &result[0], size);
            return result;
        }
    };
}