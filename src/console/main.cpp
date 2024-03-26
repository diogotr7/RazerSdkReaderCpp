#include <iostream>
#include "ChromaReader.hpp"

void handleChromaKeyboard(const ChromaKeyboard &keyboard) {
    const auto [R, G, B, A] = keyboard.GetColor(0);
    std::cout << "Color: " << std::to_string(R) << ", " << std::to_string(G) << ", " << std::to_string(B) << ", " << std::to_string(A) << std::endl;
}

void handleChromaAppData(const ChromaAppData &appData) {
    const auto app = appData.GetCurrentAppName();
    std::wcout << "App: " << app << std::endl;
}

int main() {
    auto reader = ChromaReader(handleChromaKeyboard, handleChromaAppData);

    std::cin.get();

    return 0;
}
