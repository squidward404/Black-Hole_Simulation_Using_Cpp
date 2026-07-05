# Black Hole Simulation Using C++

Minimal OpenGL simulation of a black hole.

A black hole is an object with gravity so strong that nothing, not even light, can escape once it crosses the event horizon.

![Black hole preview](image.png)

## Requirements

- CMake 3.10 or newer
- A C++17 compiler
- OpenGL
- GLFW3
- GLEW
- GLM

On Ubuntu or Debian-based systems, you can install the common dependencies with:

```bash
sudo apt install build-essential cmake libglfw3-dev libglew-dev libglm-dev
```

## Build

```bash
cmake -S . -B build
cmake --build build
./build/simulator
```