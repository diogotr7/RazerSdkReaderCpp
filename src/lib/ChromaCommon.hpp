#ifndef CHROMACOMMON
#define CHROMACOMMON
#include <chrono>
#include <cstdint>

#define ChromaStringSize 260

struct ChromaColor {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
};

struct Breathing {
    uint32_t dwParam;
    uint32_t BreathingType;
    ChromaColor Color1;
    ChromaColor Color2;
};

struct Static {
    uint32_t dwParam;
    ChromaColor Color;
};

struct Blinking {
    uint32_t dwParam;
    ChromaColor Color;
};

struct None {
    uint32_t dwParam;
};

struct Reactive {
    uint32_t dwParam;
    ChromaColor Color;
    uint32_t Duration;
};

struct SpectrumCycling {
    uint32_t dwParam;
};

struct Starlight {
    uint32_t dwParam;
    uint32_t Type;
    uint32_t Duration;
    ChromaColor Color1;
    ChromaColor Color2;
};

struct Wave {
    uint32_t dwParam;
    uint32_t Direction;
    int Speed;
};

struct ChromaDevice {
    wchar_t Instance[ChromaStringSize];
    wchar_t InstanceName[ChromaStringSize];
};
#endif