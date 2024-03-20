#ifndef CHROMAKEYBOARD
#define CHROMAKEYBOARD
#include "ChromaCommon.hpp"

struct KeyboardCustom2 {
    ChromaColor Color[132];
    ChromaColor Key[132];
};

struct KeyboardCustom3 {
    ChromaColor Color[192];
    ChromaColor Key[132];
};

struct KeyboardEffect {
    Wave Wave;
    Breathing Breathing;
    Reactive Reactive;
    Starlight Starlight;
    Static Static;
    ChromaColor Custom[132];
    KeyboardCustom2 Custom2;
    KeyboardCustom3 Custom3;
};

struct ChromaKeyboardData {
    uint32_t Flag;
    uint32_t EffectType;
    KeyboardEffect Effect;
    uint32_t Padding;
    uint64_t Timestamp;
};

struct ChromaKeyboard {
    uint32_t WriteIndex;
    int Padding;
    ChromaKeyboardData Data[10];
    ChromaDevice Device[10];
};

#endif