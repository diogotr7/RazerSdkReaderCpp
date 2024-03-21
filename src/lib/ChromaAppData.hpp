#ifndef CHROMAAPPDATA
#define CHROMAAPPDATA
#include <cstdint>

struct ChromaAppInfo {
    wchar_t AppName[ChromaStringSize];
    uint32_t AppId;
    uint32_t Padding;
};

struct ChromaAppData {
    uint32_t AppCount;
    wchar_t Unused[ChromaStringSize];
    uint32_t CurrentAppId;
    uint32_t Padding;
    ChromaAppInfo AppInfo[50];

    [[nodiscard]] std::wstring GetCurrentAppName() const {
        for (const auto &[AppName, AppId, Padding]: AppInfo) {
            if (AppId == CurrentAppId) {
                return AppName;
            }
        }

        return L"";
    }
};
#endif