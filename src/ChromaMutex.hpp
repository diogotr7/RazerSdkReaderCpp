#ifndef CHROMAMUTEX
#define CHROMAMUTEX
#include <queue>

#include "ChromaReader.hpp"
#include "Constants.h"

struct ChromaMutex {
    std::queue<HANDLE> _mutexes;

    ChromaMutex() {
        //todo: security attributes
        
        CreateMutex(nullptr, TRUE, Constants::SynapseOnlineMutex.c_str());
        Pulse(Constants::SynapseEvent);
        CreateMutex(nullptr, TRUE,Constants::OldSynapseOnlineMutex.c_str());
        Pulse(Constants::SynapseEvent);
        CreateMutex(nullptr, TRUE,Constants::OldSynapseVersionMutex.c_str());
        Pulse(Constants::SynapseEvent);
        CreateMutex(nullptr, TRUE,Constants::ChromaEmulatorMutex.c_str());
    }

    ~ChromaMutex() {
        while (!_mutexes.empty()) {
            const auto mutex = _mutexes.front();
            ReleaseMutex(mutex);
            _mutexes.pop();
        }
    }

    static void Pulse(const std::string &name) {
        auto event = OpenEvent(EVENT_ALL_ACCESS, FALSE, name.c_str());
        if (event == nullptr) {
            event = CreateEvent(nullptr, TRUE, FALSE, name.c_str());
            if (event == nullptr) {
                throw std::runtime_error("Failed to create event");
            }
        }
        PulseEvent(event);
        CloseHandle(event);
    }
};

#endif
