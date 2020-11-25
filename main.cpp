#include <iostream>
#include "Particle.h"
#include "particles_container.h"
#include "CollisionSystem.h"
int main() {


    sf::RenderWindow window(sf::VideoMode (1200, 800), "PF");
    /*
    std::vector<Particle> particles;
    for(size_t i = 0; i < 10; ++i) particles.emplace_back(new Particle(false));
    Particle p1(sf::Vector2f(45.0,45.0), sf::Vector2f(0.01,0.005), 2, 0.5, false);

    Particle p3(true);
    std::vector<std::shared_ptr<Particle> > my_vector(100);
    for(size_t i = 0; i < 100; ++i) my_vector.emplace_back(new Particle(true));
*/
    particles_container parts(100, false);
    auto *system = new CollisionSystem(parts);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        //system->simulate(10000, window);
        parts.drawContainer(window);
        for(int i = 0; i < 100; ++i) {
            parts[i]->move(105.1);
            if(parts[i]->get_posx() >= 1150 || parts[i]->get_posx() <= 1) parts[i]->set_velx(-parts[i]->get_velx());
            else if(parts[i]->get_posy() >= 799 || parts[i]->get_posy() <= 1) parts[i]->set_vely(-parts[i]->get_vely());
            for(int j = 0; j < 100; ++j) {
                if(parts[i]->collide(parts[j])) parts[i]->set_velx(-parts[i]->get_velx());
            }
        }
        window.display();
    }
}
