//
// Created by lojaz on 22/11/2020.
//

#ifndef PLSDIOSITO_PARTICLE_H
#define PLSDIOSITO_PARTICLE_H
#include "SFML/Graphics.hpp"
using namespace sf;

class Particle : public sf::Drawable{
    sf::CircleShape particle;
    Vector2f position; //current position of the particle
    Vector2f velocity;  //velocity of the particle
    double radius; //radius of each particle
    double mass; //mass of the particle
    int count; //number of collisions of each particle
    size_t id; //id of each particle
    bool sick; //if the particle is contaminated
    Color color; //color of the particle
public:
    //constructors
    Particle(Vector2f _position, Vector2f _velocity, double _radius, double _mass, bool _sick);

    Particle(bool sick);

    //destructors
    ~Particle() override;
    //methods

    //move the partcile in a straight line based on its velocity
    void move(double dt);

    //draw the particle
    virtual void draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const;

    //returns the number of collisions of this particle with walls or other particles
    int _count();

    //returns the amount of time for this particle to collide with the specified particle
    double time_to_hit(Particle *that);

    //returns the amount of time for this particle to collide with a vertical wall
    double time_to_hit_vertical_wall();

    //Returns the amount of time for this particle to collide with a horizontal wall
    double time_to_hit_horizontal_wall();

    //updates the velocities of the particles involves in a collision
    void bounce_off(Particle &that);

    //updates the velocity of this particle upon collision with a vertical wall
    void bounce_off_vertical_wall();

    //updates the velocity of this particle upon collision with a horizontal wall
    void bounce_off_horizontal_wall();

    //return the kinetic energy of this particle
    double kinetic_energy();

    //setter to give each particle a unique id -- not sure of this one
    void set_id(size_t _id);

};


#endif //PLSDIOSITO_PARTICLE_H
