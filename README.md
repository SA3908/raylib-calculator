# C++ calculator using raylib

This is a simple calculator created as a project.

A C++ project using raylib. 

## Getting started
This section shows you how to setup this project on your computer.

### Prerequisites
- **C++ compiler** - must be C++20 standard. As of now, this project will still work with basic C++20 compiler support.
- **CMake 3.11+** - install latest version available [here](https://cmake.org/download/)
  
> **NOTE**: Your build system of choice must be listed [here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).

**Example IDEs:**

MSVC compiler bundled in [Visual Studio](https://visualstudio.microsoft.com/) is a popular choice for Windows.

[Qt creator](https://www.qt.io/product/development-tools) is available for Windows/Linux, 
with an [offline installer](https://www.qt.io/offline-installers),
where you can avoid creating a QT account if you turn off your internet connection before installing.

### Installing
```sh
git clone https://github.com/SA3908/raylib-calculator.git
```

## Build
- Use build system of choice from [here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)
- Make sure that build system is installed
```sh
cmake -S . -B build -G "<build system>"
cmake --build build && cd build
ninja
```

For **Linux users**, excluding the generator option defaults to **Linux makefiles** and defaults to **MSbuild** for Windows users. 

### Ninja
- Ninja build system is cross-platform
- Install [Ninja](https://github.com/ninja-build/ninja/releases) build tool.

Run this inside this repository: 
```sh
cmake -S . -B build -G "Ninja"
cmake --build build && cd build
ninja
```
