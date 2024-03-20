#ifndef CHROMAREADER
#define CHROMAREADER
#include "SignaledReader.hpp"
#include "ChromaKeyboard.hpp"
#include "ChromaAppData.hpp"

struct ChromaReader {
    SignaledReader<ChromaKeyboard> keyboardReader;
    SignaledReader<ChromaAppData> appDataReader;
};

#endif
