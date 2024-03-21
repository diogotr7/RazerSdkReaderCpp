#ifndef CHROMAREADER
#define CHROMAREADER
#include "SignaledReader.hpp"
#include "ChromaKeyboard.hpp"
#include "ChromaAppData.hpp"
#include "ChromaMutex.hpp"
#include "Constants.hpp"

struct ChromaReader {
    ChromaMutex mutex;
    
    SignaledReader<ChromaKeyboard> keyboardReader;
    SignaledReader<ChromaAppData> appDataReader;

    ChromaReader() : keyboardReader(Constants::KeyboardFileName, Constants::KeyboardWaitHandle, handleChromaKeyboard),
                     appDataReader(Constants::AppDataFileName, Constants::AppDataWaitHandle, handleChromaAppData) {
    }

    static void handleChromaAppData(const ChromaAppData &data) {
        auto name = data.GetCurrentAppName();
        if (name.empty()) {
            std::wcout << "No app" << std::endl;
        } else {
            std::wcout << name << std::endl;
        }
    }

    static void handleChromaKeyboard(const ChromaKeyboard &keyboard) {
        const auto [R, G, B, _] = keyboard.GetColor(0);
        std::wcout << "Color: " << L"R:" << R << L" G:" << G << L" B:" << B << std::endl;
    }
};

#endif
