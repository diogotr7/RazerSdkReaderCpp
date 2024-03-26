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
    HANDLE exitEvent;
    bool isRunning;
    std::thread _thread;

    explicit SignaledReader(const std::string &memoryMappedFileName, const std::string &eventWaitHandleName,
                            std::function<void(T)> updated) : reader(memoryMappedFileName) {
        Updated = updated;
        event = OpenEvent(EVENT_ALL_ACCESS, FALSE, eventWaitHandleName.c_str());
        if (event == nullptr) {
            event = CreateEvent(nullptr, FALSE, FALSE, eventWaitHandleName.c_str());
            if (event == nullptr) {
                throw std::runtime_error("Failed to create event");
            }
        }
        exitEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        if (exitEvent == nullptr) {
            throw std::runtime_error("Failed to create exit event");
        }
        isRunning = true;
        _thread = std::thread([this] {
            this->ThreadRun();
        });
    }

    void ThreadRun() {
        const HANDLE events[2] = {event, exitEvent};
        
        if (!ResetEvent(event)) {
            throw std::runtime_error("Failed to reset event");
        }
        
        while (isRunning) {
            const DWORD result = WaitForMultipleObjects(2, events, FALSE, INFINITE);
            if (result == WAIT_OBJECT_0) {
                std::cout << "SignaledReader event "<< typeid(T).name() << std::endl;

                //fire off
                auto data = reader.data;
                Updated(*data);
            } else if (result == WAIT_OBJECT_0 + 1) {
                // Exit event was signaled
                break;
            } else {
                std::cerr << "WaitForMultipleObjects failed: " << result << std::endl;
                throw std::runtime_error("Failed to wait for event");
            }
        }
    }

    void Stop() {
        isRunning = false;
        SetEvent(exitEvent);
        if (_thread.joinable()) {
            _thread.join();
        }
    }

    ~SignaledReader() {
        std::cout << "SignaledReader destructor" << std::endl;
        Stop();
        CloseHandle(event);
        CloseHandle(exitEvent);
    }
};
#endif