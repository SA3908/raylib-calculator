# C++ calculator using raylib
## Overview
This is a simple calculator created as a project programmed in C++ using raylib for the GUI.

<img src="https://github.com/user-attachments/assets/433e31de-371a-421a-b32e-97fff784e2a2" width="300">


> **NOTE: I started this project 4 months into learning C++, bugs are expected and don't place high expectations of this project.**
## Features
- [x] **Evaluate Arithmetics**
- [X] Supports **multiple** operators 
- [x] Touch screen & mouse support with **GUI buttons**
- [x] **Keyboard** and **numpad** support for fast typing
- [x] Support for **arrow keys** to traverse through the **expression** you are typing


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
1. Use **build system** of choice from [here](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).
2. Ensure sure that build system of choice is installed.
3. ```cd``` into this **repository** you cloned.
4. Open a terminal and run a **CMake** routine similar to below:
```sh
cmake -S . -B build -G "<build system>"
cmake --build build && cd build
<build system>
```



For **Linux users**, excluding the generator option defaults to **Linux makefiles**. For Windows users it defaults to **MSbuild**. 

