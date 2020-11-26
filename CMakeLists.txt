cmake_minimum_required(VERSION 3.17)
project(OOP2_FP )

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 17)

add_executable(OOP2_FP main.cpp Particle.cpp Particle.h particles_container.cpp particles_container.h event.cpp event.h CollisionSystem.cpp CollisionSystem.h render.h)
find_package(SFML 2.5.1 COMPONENTS system window graphics)

target_link_libraries(OOP2_FP sfml-system sfml-window sfml-graphics -static)


