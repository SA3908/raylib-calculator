# C++ calculator using raylib

This is a simple calculator created as a project.

A C++ project using raylib. 

## Build
1. Install the  latest version of [CMake](https://cmake.org/download/).
2. Install a C++ compiler and debugger.
3. Clone this repository
## Windows

### Visual Studio
[Visual Studio](https://visualstudio.microsoft.com/) is an IDE by Microsoft, a free version is available called community edition. It is somewhat resource intensive and a modern computer should be used.

Make sure **"Desktop development with C++"** and **"Linux and Embedded Development with C++ is installed"**. find this repository you cloned and open it in Visual Studio and it will automatically configure. 
### Ninja
Install [Ninja](https://github.com/ninja-build/ninja/releases) build tool.

Run this inside this repository: 
```
cmake -S . -B build -G "Ninja"
cmake --build build && cd build
ninja
```

## Linux
Install **Make** build tool.

Visit [Working on GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) in raylib repository and follow the installation proccess for the libraries raylib requires.

Run:
```
cmake -S . -B build
cmake --build build && cd build
make
```
