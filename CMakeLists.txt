cmake_minimum_required(VERSION 4.3)
project(file_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(file_manager main.cpp
        include/filesystem/Node.h
        include/filesystem/File.h
        include/filesystem/Directory.h

        src/Node.cpp
        src/Directory.cpp
        include/filesystem/Filesystem.h
        src/Filesystem.cpp
        src/File.cpp
        include/ui/Screen.h
        include/ui/BrowseScreen.h
        src/Screen.cpp
        src/BrowseScreen.cpp
        include/terminal/Terminal.h
        src/Terminal.cpp
        include/app/App.h
        src/App.cpp
        include/ui/CreateFileScreen.h
        src/CreateFileScreen.cpp
        include/ui/CreateDirectoryScreen.h
        src/CreateDirectoryScreen.cpp
        include/ui/RenameScreen.h
        src/RenameScreen.cpp
        include/ui/CopyScreen.h
        include/ui/MoveScreen.h
        include/ui/DeleteScreen.h
        include/ui/SerializeScreen.h
        src/CopyScreen.cpp
        src/MoveScreen.cpp
        src/DeleteScreen.cpp
        src/SerializeScreen.cpp
)
