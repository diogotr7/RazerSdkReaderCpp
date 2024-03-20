#ifndef SIGNALEDREADER
#define SIGNALEDREADER

#include <functional>
#include <thread>

#include "MemoryMappedFileReader.hpp"

template<typename T>
class SignaledReader {
public:
    std::function<void(T)> Updated;

    MemoryMappedFileReader<T> reader;
    HANDLE event;
    bool isRunning;
    std::thread _thread;
    explicit SignaledReader(const std::string &eventWaitHandleName, const std::string &name, std::function<void(T)> updated) : reader(name) {
        Updated = updated;
        event = OpenEventA(SYNCHRONIZE, FALSE, eventWaitHandleName.c_str());
        if (event == nullptr) {
            throw std::runtime_error("Failed to open event");
        }
        isRunning = true;
        _thread = std::thread([this]() {
            this->ThreadRun();
        });
    }

    void ThreadRun() {
        while (isRunning) {
            if (auto result = WaitForSingleObject(event, INFINITE); result != WAIT_OBJECT_0) {
                throw std::runtime_error("Failed to wait for event");
            }

            //fire off
            auto data = reader.data;
            Updated(*data);
        }
    }

    ~SignaledReader() {
        isRunning = false;
        if (_thread.joinable()) {
            _thread.join();
        }
        CloseHandle(event);
    }
};
#endif