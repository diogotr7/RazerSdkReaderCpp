cmake_minimum_required(VERSION 3.28)
project(RazerSdkReaderCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(RazerSdkReaderCpp main.cpp
        ChromaKeyboard.hpp
        ChromaCommon.hpp
        ChromaEncryption.hpp
        ChromaAppData.hpp
        MemoryMappedFileReader.hpp
        SignaledReader.hpp
        ChromaReader.hpp
        Constants.h
        ChromaMutex.hpp
        Utils.hpp)
