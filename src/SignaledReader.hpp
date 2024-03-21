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

    explicit SignaledReader(const std::string &memoryMappedFileName, const std::string &eventWaitHandleName,
                            std::function<void(T)> updated) : reader(memoryMappedFileName) {
        Updated = updated;
        auto access = 2031619u;
        event = OpenEventA(2031619u, FALSE, eventWaitHandleName.c_str());
        if (event == nullptr) {
            event = CreateEventA(nullptr, FALSE, FALSE, eventWaitHandleName.c_str());
            if (event == nullptr) {
                throw std::runtime_error("Failed to create event");
            }
        }
        isRunning = true;
        _thread = std::thread([this] {
            this->ThreadRun();
        });
    }

    void ThreadRun() {
        auto data = reader.data;
        Updated(*data);
        
        if (!ResetEvent(event)) {
            throw std::runtime_error("Failed to reset event");
        }
        
        while (isRunning) {
            //todo: cancel this wait somehow when the program is closing
            if (auto result = WaitForSingleObject(event, INFINITE); result != WAIT_OBJECT_0) {
                throw std::runtime_error("Failed to wait for event");
            }
            
            std::cout << "SignaledReader event" << std::endl;

            //fire off
            auto data = reader.data;
            Updated(*data);
        }
    }

    ~SignaledReader() {
        std::cout << "SignaledReader destructor" << std::endl;
        isRunning = false;
        if (_thread.joinable()) {
            _thread.join();
        }
        CloseHandle(event);
    }
};
#endif
