//
// Created by lojaz on 25/11/2020.
//

#ifndef OOP2_FP_RENDER_H
#define OOP2_FP_RENDER_H


#include "Particle.h"
#include "particles_container.h"
#include "CollisionSystem.h"

particles_container parts(400, false);

void events(sf::RenderWindow &window){
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:{
                window.close();
                break;
            }
            case sf::Event::MouseButtonPressed:{
                if (event.mouseButton.button == sf::Mouse::Left){
                    std::shared_ptr<Particle> t1 = std::make_shared<Particle>(true);
                    t1->set_posx(event.mouseButton.x);
                    t1->set_vely(event.mouseButton.y);
                    parts.add(t1);;
                }
            }
        }
    }
}

void Render() {
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Particle Simulation");

    //CollisionSystem system(parts);
    std::shared_ptr<Particle> t1 = std::make_shared<Particle>(true);
    std::shared_ptr<Particle> t2 = std::make_shared<Particle>(true);
    std::shared_ptr<Particle> t3 = std::make_shared<Particle>(true);
    std::shared_ptr<Particle> t4 = std::make_shared<Particle>(true);
    parts.add(t1);
    parts.add(t2);
    parts.add(t3);
    parts.add(t4);
    while (window.isOpen()) {
        events(window);
        window.clear();
        //system.simulate(10000, window);
        parts.naive_implementation(window);
        window.display();
    }
}




#endif //OOP2_FP_RENDER_H
