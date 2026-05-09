cmake_minimum_required(VERSION 4.1)
project(P2_CE2103_TankAttack)

set(CMAKE_CXX_STANDARD 14)

add_executable(P2_CE2103_TankAttack
        src/main.cpp
        src/core/Graph.cpp
        src/core/Graph.h
        src/core/Queue.cpp
        src/core/Queue.h
        src/core/MapGenerator.cpp
        src/core/MapGenerator.h)
