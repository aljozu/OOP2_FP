//
// Created by lojaz on 23/11/2020.
//

#include "particles_container.h"



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
    for(int i = 0; i < copy.size(); ++i) particle_container[i] = copy[i];
    return *this;
}

void particles_container::naive_implementation(RenderWindow &window) {
    drawContainer(window);
    //std::vector<pair<*std::shared_ptr<Particle>, *std::shared_ptr<Particle>>> coll;
    for (auto & i : particle_container) {
        i->move(10.0);
        if(i->get_posx() >= 1150 || i->get_posx() <= 1) i->set_velx(-i->get_velx());
        else if(i->get_posy() >= 799 || i->get_posy() <= 1) i->set_vely(-i->get_vely());
        for(auto & j : particle_container) {
            if(i != j) {
                if (i->collide(j)) {
                    //to prevent overlap between particles
                    double distance = sqrt((i->get_posx()-j->get_posx())*(i->get_posx()-j->get_posx()) + (i->get_posy()-j->get_posy())*(i->get_posy()-j->get_posy()));
                    double foverlap = 0.5*(distance - i->get_radius() - j->get_radius());

                    i->set_posx(i->get_posx()-(foverlap * ((i->get_posx() - j->get_posx()) / distance)));
                    i->set_posy(i->get_posy()-(foverlap * ((i->get_posx() - j->get_posx()) / distance)));

                    j->set_posx(j->get_posx()+(foverlap * ((i->get_posx() - j->get_posx()) / distance)));
                    j->set_posy(j->get_posy()+(foverlap * ((i->get_posx() - j->get_posx()) / distance)));

                    //update velocity when two particles collide
                    double dist = i->get_radius() + j->get_radius();
                    double mag = i->magnitude(j);
                    double fx = mag * (i->get_posx() - j->get_posx()) / dist;
                    double fy = mag * (i->get_posy() - j->get_posy()) / dist;

                    i->set_velx(i->get_velx() + i->get_velx() + fx / i->get_mass());
                    i->set_vely(i->get_vely() + i->get_vely() + fx / i->get_mass());

                    j->set_velx(j->get_velx() - j->get_velx() + fy / j->get_mass());
                    j->set_vely(j->get_vely() - j->get_vely() + fy / j->get_mass());
                }
            }
        }
    }
}

particles_container::particles_container() = default;

particles_container::~particles_container() = default;



