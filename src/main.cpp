#include <cstdint>
#include <iostream>
#include <Windows.h>
#include "ChromaCommon.hpp"
#include "ChromaKeyboard.hpp"
#include "ChromaAppData.hpp"
#include "SignaledReader.hpp"

void handleChromaAppData(const ChromaAppData &data) {
    std::wcout << data.GetCurrentAppName() << std::endl;
}


int main() {
    auto reader = SignaledReader<ChromaAppData>(
        "Global\\{190E28CB-BB73-46B1-8FFD-62FF0EE273A0}",
        "Global\\{D4E1A960-872F-4BF8-B09A-9E54F646D7CE}",
        handleChromaAppData
    );

    std::cin.get();
}

