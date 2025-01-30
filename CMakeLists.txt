cmake_minimum_required(VERSION 3.27)
project(ex3)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 main.cpp
        Vector.cpp
        Vector.h
        Controller.cpp
        Controller.h
        View.cpp
        View.h
        ImperialAgent.cpp
        ImperialAgent.h
        Shipman.cpp
        Shipman.h
        Commander.cpp
        Commander.h
        Admiral.cpp
        Admiral.h
        SpaceStation.cpp
        SpaceStation.h
        FortressStar.cpp
        FortressStar.h
        SpaceShip.cpp
        SpaceShip.h
        Model.cpp
        Model.h
        AgentFactory.cpp
        AgentFactory.h
        ShipmanFactory.cpp
        ShipmanFactory.h
        CommanderFactory.cpp
        CommanderFactory.h
        AdmiralFactory.cpp
        AdmiralFactory.h
        Shuttle.cpp
        Shuttle.h
        Falcon.cpp
        Falcon.h
        Bomber.cpp
        Bomber.h
        Destroyer.cpp
        Destroyer.h
        Object.cpp
        Object.h
        Rocket.cpp
        Rocket.h
        Utilities.cpp
        Utilities.h
)
