cmake_minimum_required(VERSION 3.12)
project(newex2 C)

set(CMAKE_C_STANDARD 99)

add_executable(newex2 cmake-build-debug/battleships_game.c cmake-build-debug/battleships.c cmake-build-debug/battleships.h)