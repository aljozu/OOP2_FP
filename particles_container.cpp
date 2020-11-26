//
// Created by lojaz on 23/11/2020.
//

#include "particles_container.h"

particles_container::particles_container() = default;

particles_container::~particles_container() = default;

particles_container::particles_container(size_t size, bool sick) {
    if(size > 0){
        for(size_t i = 0; i < size; ++i) particle_container.emplace_back(std::make_shared<Particle>(sick));
    }
}

void particles_container::draw(RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    for (const auto & i : particle_container) {
        renderTarget.draw(*i);
    }
   // sf::Time t3 = sf::seconds(0.2);
}

void particles_container::drawContainer(RenderWindow &window) {
    for (auto & i : particle_container) {
        window.draw(*i);
    }
   // sf::Time t3 = sf::seconds(0.2);
}

size_t particles_container::size() {
    return particle_container.size();
}

void particles_container::add(std::shared_ptr<Particle> &a) {
    particle_container.push_back(a);
}

std::shared_ptr<Particle> &particles_container::operator[](int index) {
    if(index > particle_container.size()) throw std::runtime_error("The index is greater than the container size");
    else return particle_container[index];
}

particles_container &particles_container::operator=(const std::vector<std::shared_ptr<Particle>>& copy) {
    for(int i = 0; i < copy.size(); ++i) particle_container[i] = copy[i];
    return *this;
}

inline void set_new_pos(std::shared_ptr<Particle> &i, std::shared_ptr<Particle> &j){
    //to prevent overlap between particles
    double distance = sqrt((i->get_posx()-j->get_posx())*(i->get_posx()-j->get_posx()) + (i->get_posy()-j->get_posy())*(i->get_posy()-j->get_posy()));
    double foverlap = 0.5*(distance - i->get_radius() - j->get_radius());

    //assign new positions to the particles to avoid overlap
    i->set_posx(i->get_posx()-(foverlap * ((i->get_posx() - j->get_posx()) / distance)));
    i->set_posy(i->get_posy()-(foverlap * ((i->get_posx() - j->get_posx()) / distance)));

    j->set_posx(j->get_posx()+(foverlap * ((i->get_posx() - j->get_posx()) / distance)));
    j->set_posy(j->get_posy()+(foverlap * ((i->get_posx() - j->get_posx()) / distance)));
}

inline void set_new_vel(std::shared_ptr<Particle> &i, std::shared_ptr<Particle> &j){
    //assign new positions to the particles to avoid overlap
    double distance = sqrt((i->get_posx()-j->get_posx())*(i->get_posx()-j->get_posx()) + (i->get_posy()-j->get_posy())*(i->get_posy()-j->get_posy()));
    //normal
    double nx = (j->get_posx() - i->get_posx())/ distance;
    double ny = (j->get_posy() - i->get_posy())/ distance;
    //tangent
    double tx = -ny;
    double ty = nx;
    //dot product tangent
    double dp_tan1 = i->get_velx() * tx + i->get_vely() * ty;
    double dp_tan2 = j->get_velx() * tx + j->get_vely() * ty;
    //dot product normal
    float dp_Norm1 = i->get_velx() * nx + i->get_vely() * ny;
    float dp_Norm2 = j->get_velx() * nx + j->get_vely() * ny;
    //conservation of momentum
    double m1 = (dp_Norm1 * (i->get_mass() - j->get_mass()) + 2.0f * i->get_mass() * dp_Norm2) / (i->get_mass() + j->get_mass());
    double m2 = (dp_Norm2 * (j->get_mass() - i->get_mass()) + 2.0f * i->get_mass() * dp_Norm1) / (i->get_mass() + j->get_mass());
    //update the velocities
    i->set_velx(tx * dp_tan1 + nx * m1);
    i->set_vely(ty * dp_tan1 + ny * m1);

    j->set_velx(tx * dp_tan2 + nx * m2);
    j->set_vely(ty * dp_tan2 + ny * m2);
}

void particles_container::naive_implementation(RenderWindow &window) {
    window.clear();
    drawContainer(window);

    for (auto & i : particle_container) {
        i->move(60.0);

        //check for wall collisions
        if(i->get_posx() >= Width || i->get_posx() <= 1) i->set_velx(-i->get_velx());
        else if(i->get_posy() >= Height || i->get_posy() <= 1) i->set_vely(-i->get_vely());

        //check for particle - particle collision
        for(auto & j : particle_container) {
            if(i != j) {
                if (i->collide(j)) {
                    if(i->get_color() == sf::Color::Green) i->set_color(j->get_color());
                    //move the particles in order to avoid overlap
                    set_new_pos(i, j);

                    //update velocity when two particles collide
                    set_new_vel(i, j);
                }
            }
        }
    }
}








