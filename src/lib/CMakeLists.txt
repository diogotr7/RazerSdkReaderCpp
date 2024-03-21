cmake_minimum_required(VERSION 3.28)
project(RazerSdkReaderCpp)

set(CMAKE_CXX_STANDARD 20)


add_library(RazerSdkReaderCpp STATIC
        ChromaKeyboard.hpp
        ChromaCommon.hpp
        ChromaEncryption.hpp
        ChromaAppData.hpp
        MemoryMappedFileReader.hpp
        SignaledReader.hpp
        ChromaReader.hpp
        Constants.hpp
        ChromaMutex.hpp
        Utils.hpp)

set_target_properties(RazerSdkReaderCpp PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(RazerSdkReaderCpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
