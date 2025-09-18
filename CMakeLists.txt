cmake_minimum_required(VERSION 4.0)
project(unisinosRPG)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(unisinosRPG
        .idea/.gitignore
        .idea/editor.xml
        .idea/modules.xml
        .idea/unisinosRPG.iml
        .idea/vcs.xml
        .idea/workspace.xml
        include/Course.h
        include/Entity.h
        include/Game.h
        include/Item.h
        include/Scene.h
        include/Student.h
        src/Course.cpp
        src/Entity.cpp
        src/Game.cpp
        src/Item.cpp
        src/Scene.cpp
        src/Student.cpp
        main.cpp
        README.md)
