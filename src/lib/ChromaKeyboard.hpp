#ifndef CHROMAKEYBOARD
#define CHROMAKEYBOARD
#include "ChromaCommon.hpp"
#include "ChromaEncryption.hpp"
#include "Utils.hpp"

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

struct ChromaKeyboard final {
    uint32_t WriteIndex;
    int Padding;
    ChromaKeyboardData Data[10];
    ChromaDevice Device[10];
    
    [[nodiscard]] static uint32_t GetWidth() {
        return 22;
    }

    [[nodiscard]] static uint32_t GetHeight() {
        return 6;
    }

    [[nodiscard]] ChromaColor GetColor(const int32_t index) const {
        const auto frame = &Data[ToReadIndex(WriteIndex)];

        switch(frame->EffectType) {
            //static
            case 6: return ChromaEncryption::Decrypt(frame->Effect.Static.Color, frame->Timestamp);
            //customKey
            case 8: return ChromaEncryption::Decrypt(frame->Effect.Custom2.Key[index], frame->Timestamp);
            //any other effect
            default: return ChromaEncryption::Decrypt(frame->Effect.Custom[index], frame->Timestamp);
        }
    }

    void GetColors(ChromaColor* colors) const {
        const auto frame = &Data[ToReadIndex(WriteIndex)];
        const auto effect = frame->Effect.Custom;
        const auto length = GetWidth() * GetHeight();

        //TODO: use different effect when available
        ChromaEncryption::Decrypt(effect, colors,length, frame->Timestamp);
    }
};

#endif