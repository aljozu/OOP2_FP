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
    for (auto & i : particle_container) {
        window.draw(*i);
    }
}

particles_container::particles_container() = default;

particles_container::~particles_container() = default;



