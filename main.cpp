
#include "Particle.h"
#include "particles_container.h"
int main() {
    int x = 10000;
    sf::RenderWindow window(sf::VideoMode (600, 600), "PF");
    std::vector<Particle> particles;
    for(size_t i = 0; i < 10; ++i) particles.emplace_back(new Particle(false));
    Particle p1(sf::Vector2f(45.0,45.0), sf::Vector2f(0.01,0.005), 2, 0.5, false);
    particles_container parts(100, false);
    Particle p3(true);
    std::vector<std::shared_ptr<Particle> > my_vector(100);
    for(size_t i = 0; i < 100; ++i) my_vector.emplace_back(new Particle(true));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
       // parts.drawContainer(window);


           window.clear();
           window.draw(parts);
           window.display();

    }
}
