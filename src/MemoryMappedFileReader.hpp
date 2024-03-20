#ifndef MEMORYMAPPEDFILEREADER
#define MEMORYMAPPEDFILEREADER
#include <iostream>
#include <string>
#include <Windows.h>

template<typename T>
class MemoryMappedFileReader {
public:
    explicit MemoryMappedFileReader(const std::string &memoryMappedFileName) {
        mmFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            FALSE,
            memoryMappedFileName.c_str());

        if (mmFile == nullptr) {
            std::cerr << "OpenFileMapping failed: " << GetLastError() << std::endl;
            return;
        }

        mmView = MapViewOfFile(
            mmFile,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            sizeof(T));

        data = static_cast<T *>(mmView);
    }

    ~MemoryMappedFileReader() {
        UnmapViewOfFile(mmView);
        CloseHandle(mmFile);
    }

    T *data;
    HANDLE mmFile;
    LPVOID mmView;
};

#endif