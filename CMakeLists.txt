cmake_minimum_required(VERSION 3.10)
project(BlackHoleSim)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(simulator src/main.cpp)

target_link_libraries(simulator OpenGL::GL glfw GLEW::GLEW glm::glm)   
