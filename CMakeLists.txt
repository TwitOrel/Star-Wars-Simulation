cmake_minimum_required(VERSION 3.27)
project(ex3)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 main.cpp
        ./src/Vector.cpp
        ./header/Vector.h
        ./src/Controller.cpp
        ./header/Controller.h
        ./src/View.cpp
        ./header/View.h
        ./src/ImperialAgent.cpp
        ./header/ImperialAgent.h
        ./src/Shipman.cpp
        ./header/Shipman.h
        ./src/Commander.cpp
        ./header/Commander.h
        ./src/Admiral.cpp
        ./header/Admiral.h
        ./src/SpaceStation.cpp
        ./header/SpaceStation.h
        ./src/FortressStar.cpp
        ./header/FortressStar.h
        ./src/SpaceShip.cpp
        ./header/SpaceShip.h
        ./src/Model.cpp
        ./header/Model.h
        ./src/AgentFactory.cpp
        ./header/AgentFactory.h
        ./src/ShipmanFactory.cpp
        ./header/ShipmanFactory.h
        ./src/CommanderFactory.cpp
        ./header/CommanderFactory.h
        ./src/AdmiralFactory.cpp
        ./header/AdmiralFactory.h
        ./src/Shuttle.cpp
        ./header/Shuttle.h
        ./src/Falcon.cpp
        ./header/Falcon.h
        ./src/Bomber.cpp
        ./header/Bomber.h
        ./src/Destroyer.cpp
        ./header/Destroyer.h
        ./src/Object.cpp
        ./header/Object.h
        ./src/Rocket.cpp
        ./header/Rocket.h
        ./src/Utilities.cpp
        ./header/Utilities.h
)
