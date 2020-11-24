cmake_minimum_required(VERSION 3.17)
project(plsdiosito)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 17)

add_executable(plsdiosito main.cpp Particle.cpp Particle.h particles_container.cpp particles_container.h)
find_package(SFML 2.5.1 COMPONENTS system window graphics)

target_link_libraries(plsdiosito sfml-system sfml-window sfml-graphics -static)


