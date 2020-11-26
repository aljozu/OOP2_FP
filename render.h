//
// Created by lojaz on 25/11/2020.
//

#ifndef OOP2_FP_RENDER_H
#define OOP2_FP_RENDER_H


#include "Particle.h"
#include "particles_container.h"
#include "CollisionSystem.h"


void events(sf::RenderWindow &window){
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void Render() {
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Particle Simulation");

    particles_container parts(400, false);
    //CollisionSystem system(parts);

    while (window.isOpen()) {
        events(window);
        window.clear();
        //system.simulate(10000, window);
        parts.naive_implementation(window);
        window.display();
    }
}



#endif //OOP2_FP_RENDER_H
