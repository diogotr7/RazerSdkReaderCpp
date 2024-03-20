﻿#ifndef CHROMAENCRYPTION
#define CHROMAENCRYPTION
#include <cstdint>
#include <vector>
#include <experimental/simd>
#include "ChromaCommon.hpp"

struct ChromaEncryption {
    static uint8_t Key[128];

    ChromaEncryption() {
        const uint8_t originalKey[] = {
            0x45, 0x86, 0x56, 0x02, 0x34, 0x86, 0x27, 0xF6, 0xD6, 0x16, 0x02, 0x75,
            0xF6, 0x27, 0xB6, 0x37, 0x86, 0xF6, 0x07, 0x02, 0x96, 0x37, 0x02, 0x97,
            0xF6, 0x57, 0x27, 0x02, 0xF6, 0xE6, 0x56, 0xD2, 0x37, 0x47, 0xF6, 0x07,
            0xD2, 0x37, 0x86, 0xF6, 0x07, 0x02, 0x47, 0xF6, 0x02, 0x76, 0x56, 0x47,
            0x02, 0x47, 0x86, 0x56, 0x02, 0xD6, 0xF6, 0x37, 0x47, 0x02, 0xF6, 0x57,
            0x47, 0x02, 0xF6, 0x66, 0x02, 0x97, 0xF6, 0x57, 0x27, 0x02, 0x34, 0x86,
            0x27, 0xF6, 0xD6, 0x16, 0x02, 0x46, 0x56, 0x67, 0x96, 0x36, 0x56, 0x37,
            0xE2, 0x02, 0x02, 0x75, 0x86, 0x56, 0x47, 0x86, 0x56, 0x27, 0x02, 0x96,
            0x47, 0x72, 0x37, 0x02, 0x37, 0xD6, 0x16, 0x27, 0x47, 0x02, 0xC6, 0x96,
            0x76, 0x86, 0x47, 0x96, 0xE6, 0x76, 0x02, 0x26, 0x16, 0x37, 0x56, 0x46,
            0x02, 0xF6, 0xE6, 0x02, 0x96, 0xE6, 0xD2, 0xF6, 0x75, 0x56, 0x29, 0x27,
            0x56, 0x02, 0x07, 0x57, 0x37, 0x86, 0x96, 0xE6, 0x76, 0x02, 0x47, 0x86,
            0x56, 0x02, 0xC6, 0x96, 0xD6, 0x96, 0x47, 0x37, 0x02, 0x47, 0xF6, 0x02,
            0x77, 0x86, 0x16, 0x47, 0x02, 0x16, 0x02, 0x76, 0x16, 0xD6, 0x96, 0xE6,
            0x76, 0x02, 0xC6, 0x16, 0x07, 0x47, 0xF6, 0x07, 0x02, 0x36, 0x16, 0xE6,
            0x02, 0x46, 0xF6, 0xE2, 0x02, 0x45, 0x86, 0x56, 0x02, 0x25, 0x16, 0xA7,
            0x56, 0x27, 0x02, 0x24, 0xC6, 0x16, 0x46, 0x56, 0x02, 0x05, 0x27, 0xF6,
            0x02, 0x13, 0x73, 0x02, 0x96, 0x37, 0x02, 0x26, 0x57, 0x96, 0xC6, 0x47,
            0x02, 0x77, 0x96, 0x47, 0x86, 0x02, 0x16, 0x02, 0x07, 0xF6, 0x77, 0x56,
            0x27, 0x66, 0x57, 0xC6, 0x02, 0x07, 0x27, 0xF6, 0x36, 0x56, 0x37, 0x37,
            0xF6, 0x27, 0x02, 0x47, 0xF6, 0x02, 0x27, 0x57, 0xE6, 0x02, 0x07, 0x56,
            0x27, 0x66, 0xF6, 0x12, 0x24, 0x57, 0x96, 0xC6, 0x47, 0x02, 0x96, 0xE6,
            0x47, 0xF6, 0x02, 0xF6, 0x57, 0x27, 0x02, 0x44, 0xE4, 0x14, 0xC2, 0x02,
            0x47, 0x86, 0x56, 0x02, 0x25, 0x16, 0xA7, 0x56, 0x27, 0x02, 0x05, 0x86,
            0xF6, 0xE6, 0x56, 0x02, 0x23, 0x02, 0x66, 0x56, 0x16, 0x47, 0x57, 0x27,
            0x56, 0x37, 0x02, 0x16, 0xE6, 0x02, 0x96, 0xC6, 0xC6, 0x57, 0xD6, 0x96,
            0xE6, 0x16, 0x47, 0x56, 0x46, 0x02, 0x25, 0x16, 0xA7, 0x56, 0x27, 0x02,
            0xC6, 0xF6, 0x76, 0xF6, 0x02, 0x77, 0x96, 0x47, 0x86, 0x02, 0x36, 0x57,
            0x37, 0x47, 0xF6, 0xD6, 0x96, 0xA7, 0x16, 0x26, 0xC6, 0x56, 0x02, 0x25,
            0x16, 0xA7, 0x56, 0x27, 0x02, 0x34, 0x86, 0x27, 0xF6, 0xD6, 0x16, 0x99,
            0x02, 0x25, 0x74, 0x24, 0x02, 0xC6, 0x96, 0x76, 0x86, 0x47, 0x96, 0xE6,
            0x76, 0xE2, 0x02, 0x95, 0xF6, 0x57, 0x27, 0x02, 0xD6, 0xF6, 0x26, 0xBB,
            0x45, 0x86, 0x56, 0x02, 0x25, 0x16, 0xA7, 0x56, 0x27, 0x02, 0x34, 0x86,
            0x27, 0xF6, 0xD6, 0x16, 0x02, 0x34, 0xF6, 0xE6, 0xE6, 0x56, 0x36, 0x47,
            0x56, 0x46, 0x02, 0x44, 0x56, 0x67, 0x96, 0x36, 0x56, 0x37, 0x02, 0x05,
            0x27, 0xF6, 0x76, 0x27, 0x16, 0xD6, 0x02, 0x77, 0x96, 0xC6, 0xC6, 0x02,
            0x56, 0xE6, 0x16, 0x26, 0xC6, 0x56, 0x02, 0x07, 0x16, 0x27, 0x47, 0xE6,
            0x56, 0x27, 0x37, 0x02, 0x47, 0xF6, 0x02, 0x56, 0xE6, 0x16, 0x26, 0xC6,
            0x56, 0x02, 0x34, 0x86, 0x27, 0xF6, 0xD6, 0x16, 0x02, 0xC6, 0x96, 0x76,
            0x86, 0x47, 0x96, 0xE6, 0x76, 0x02, 0x47, 0x86, 0x27, 0xF6, 0x57, 0x76,
            0x86, 0x02, 0x16, 0x02, 0x37, 0x96, 0xE6, 0x76, 0xC6, 0x56, 0x02, 0x36,
            0xC6, 0x96, 0x36, 0xB6, 0x02, 0xF6, 0xE6, 0x02, 0x47, 0x86, 0x56, 0x96,
            0x27, 0x02, 0x37, 0xF6, 0x66, 0x47, 0x77, 0xA0
        };

        for (int i = 0; i < 128; i++) {
            int correctedIndex = i;
            if (correctedIndex > 124) {
                correctedIndex -= 3;
            }

            const auto r = originalKey[0 * 128 + 0 + correctedIndex];
            const auto g = originalKey[1 * 128 + 1 + correctedIndex];
            const auto b = originalKey[2 * 128 + 2 + correctedIndex];
            const auto a = originalKey[3 * 128 + 3 + correctedIndex];

            Key[i] = (r << 24) | (g << 16) | (b << 8) | a;
        }
    }

    static ChromaColor Decrypt(ChromaColor color, const uint64_t timestamp) {
        const uint32_t key = Key[timestamp % 128];
        const uint32_t colorAsInt = *reinterpret_cast<uint32_t *>(&color);
        uint32_t xora = colorAsInt ^ key | 0xFF000000;
        return *reinterpret_cast<ChromaColor *>(&xora);
    }

    static void Decrypt(std::vector<ChromaColor> input, std::vector<ChromaColor> output,
                        const uint64_t timestamp) {
        const uint32_t smallest = std::min(input.size(), output.size());
        const uint32_t key = Key[timestamp % 128];
        for (uint32_t i = 0; i < smallest; i++) {
            const uint32_t colorAsInt = *reinterpret_cast<uint32_t *>(&input[i]);
            uint32_t xora = colorAsInt ^ key | 0xFF000000;
            output[i] = *reinterpret_cast<ChromaColor *>(&xora);
        }
    }
};
#endif
