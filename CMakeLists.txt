cmake_minimum_required(VERSION 4.1)
project(P2_CE2103_TankAttack)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "C:/SFML/SFML-3.1.0/lib/cmake/SFML") #cambiar dirección a carpeta propia

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(P2_CE2103_TankAttack
        src/main.cpp
        src/core/Graph.cpp
        src/core/Graph.h
        src/core/Queue.cpp
        src/core/Queue.h
        src/core/MapGenerator.cpp
        src/core/MapGenerator.h
        src/core/Pathfinding.cpp
        src/core/Pathfinding.h
        src/rendering/MapRenderer.cpp
        src/rendering/MapRenderer.h
        src/core/Tank.cpp
        src/core/Tank.h
        src/core/GameManager.cpp
        src/core/GameManager.h
        src/pathfinding/LineOfSight.cpp
        src/pathfinding/LineOfSight.h
        src/combat/Bullet.h
        src/combat/Bullet.cpp
        src/rendering/TankRenderer.cpp
        src/rendering/TankRenderer.h
        src/pathfinding/RandomMovement.cpp
        src/pathfinding/RandomMovement.h
        src/combat/BulletManager.cpp
        src/combat/BulletManager.h
        src/powerups/PowerUp.h
        src/powerups/PowerUpQueue.h
        src/powerups/PowerUpQueue.cpp
        src/rendering/TraceRenderer.cpp
        src/rendering/TraceRenderer.h)

target_include_directories(P2_CE2103_TankAttack PRIVATE src)
link_directories("C:/SFML/SFML-3.1.0/lib") #cambiar dirección a carpeta propia
target_link_libraries(P2_CE2103_TankAttack SFML::Graphics)