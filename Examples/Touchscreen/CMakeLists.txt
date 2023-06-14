cmake_minimum_required(VERSION 3.25)
project(Screen CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)
set(ARDUINO_SDK_PATH C:/Program Files/WindowsApps/ArduinoLLC.ArduinoIDE_1.8.57.0_x86__mdqgnx93n4wtt)
set(ARDUINO_DEFAULT_BOARD "unPhone 9")
set(ARDUINO_DEFAULT_PORT "COM9")


include_directories(.)

add_executable(Screen
    build_opt.h
    Screen.ino)
