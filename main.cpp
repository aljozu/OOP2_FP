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
        parts.naive_implementation(window);

        window.display();
    }
}
