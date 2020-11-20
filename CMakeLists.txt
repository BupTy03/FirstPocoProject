cmake_minimum_required(VERSION 3.17)
project(PocoFirstProject)

set(CMAKE_CXX_STANDARD 14)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
        REQUIRES Poco/1.10.1@pocoproject/stable
        BUILD missing)
conan_define_targets()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)



add_executable(PocoFirstProject
        main.cpp
        SimpleEchoServer.cpp SimpleEchoServer.h
        SimpleRequestHandler.cpp SimpleRequestHandler.h)

target_link_libraries(PocoFirstProject PRIVATE CONAN_PKG::Poco)
