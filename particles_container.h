//
// Created by lojaz on 23/11/2020.
//

#ifndef PLSDIOSITO_PARTICLES_CONTAINER_H
#define PLSDIOSITO_PARTICLES_CONTAINER_H
#include "Particle.h"


class particles_container : public sf::Drawable {
    std::vector<std::shared_ptr<Particle>> particle_container;
    bool sick;
    //std::vector<Particle> particle_container;
    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;
public:
    //default constructor
    particles_container();

    //constructor with a number of given particles
    explicit particles_container(size_t size, bool sick);

    //default destructor
    ~particles_container() override;

    //returns the container
    std::vector<std::shared_ptr<Particle>> getContainer();

    //another function to draw
    void drawContainer(sf::RenderWindow &window);

    //size of the container
    size_t size();

    //ovearloading the [] operator
    std::shared_ptr<Particle> & operator[](int);

    //overloading the assignment operator
    particles_container & operator=(const std::vector<std::shared_ptr<Particle>>&);
};


#endif //PLSDIOSITO_PARTICLES_CONTAINER_H
