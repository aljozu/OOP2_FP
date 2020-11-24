//
// Created by lojaz on 23/11/2020.
//

#include "particles_container.h"

#include <memory>

void particles_container::draw(RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    for (const auto & i : particle_container) {
        renderTarget.draw(*i);
    }
}

particles_container::particles_container(size_t size, bool sick) {
    if(size > 0){
        for(size_t i = 0; i < size; ++i) particle_container.emplace_back(std::make_shared<Particle>(sick));
    }
}

std::vector<std::shared_ptr<Particle>> particles_container::getContainer() {
    return particle_container;
}

void particles_container::drawContainer(RenderWindow &window) {
    //window.clear(sf::Color::Black);
    for (auto & i : particle_container) {
        window.draw(*i);
    }
    window.display();
    sf::Time t3 = sf::seconds(0.2);
}

size_t particles_container::size() {
    return particle_container.size();
}

std::shared_ptr<Particle> &particles_container::operator[](int index) {
    if(index > particle_container.size()) throw std::runtime_error("The index is greater than the container size");
    else return particle_container[index];
}

particles_container &particles_container::operator=(const std::vector<std::shared_ptr<Particle>>& copy) {
    particles_container temporal;
    for(int i = 0; i < copy.size(); ++i) particle_container[i] = copy[i];
    return *this;
}

particles_container::particles_container() = default;

particles_container::~particles_container() = default;



