#ifndef CHROMAREADER
#define CHROMAREADER
#include "SignaledReader.hpp"
#include "ChromaKeyboard.hpp"
#include "ChromaAppData.hpp"
#include "ChromaMutex.hpp"
#include "Constants.hpp"

using KbHandler = std::function<void(const ChromaKeyboard &)>;
using AppDataHandler = std::function<void(const ChromaAppData &)>;

struct ChromaReader {
    ChromaMutex mutex;

    SignaledReader<ChromaKeyboard> keyboardReader;
    SignaledReader<ChromaAppData> appDataReader;

    KbHandler handleChromaKeyboard;
    AppDataHandler handleChromaAppData;

    ChromaReader(const KbHandler &_handleChromaKeyboard, const AppDataHandler &_handleChromaAppData)
    : keyboardReader(Constants::KeyboardFileName, Constants::KeyboardWaitHandle,_handleChromaKeyboard),
        appDataReader(Constants::AppDataFileName,Constants::AppDataWaitHandle, _handleChromaAppData)
    {
        
    }
};

#endif
