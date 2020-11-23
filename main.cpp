#include <iostream>
#include <vector>
#include <memory>
#include "Particle.h"
int main() {
    sf::RenderWindow window(sf::VideoMode (600, 600), "PF");
    std::vector<Particle> particles;
    Particle p1(sf::Vector2f(45.0,45.0), sf::Vector2f(0.01,0.005), 2, 0.5, false);

    Particle p3(true);


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
            window.draw(p3);
            window.draw(p1);
            p3.move(10);
            p1.move(5);

            window.display();
    }
}
