//
// Created by lojaz on 22/11/2020.
//

#ifndef PLSDIOSITO_PARTICLE_H
#define PLSDIOSITO_PARTICLE_H
#include "SFML/Graphics.hpp"
#include <memory>
#include <cmath>
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
    Particle();
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
    double time_to_hit(std::shared_ptr<Particle> that);

    //returns the amount of time for this particle to collide with a vertical wall
    double time_to_hit_vertical_wall();

    //Returns the amount of time for this particle to collide with a horizontal wall
    double time_to_hit_horizontal_wall();

    //updates the velocities of the particles involves in a collision
    void bounce_off(std::shared_ptr<Particle>& that);

    //updates the velocity of this particle upon collision with a vertical wall
    void bounce_off_vertical_wall();

    //updates the velocity of this particle upon collision with a horizontal wall
    void bounce_off_horizontal_wall();

    //return the kinetic energy of this particle
    double kinetic_energy();

    //setter to give each particle a unique id -- not sure of this one
    void set_id(size_t _id);

    double get_posx(){return position.x;}
    double get_posy(){return position.y;}
    void set_velx(double v){velocity.x = v;}
    void set_vely(double v){velocity.y = v;}
    double get_velx(){return velocity.x;}
    double get_vely(){return velocity.y;}

    bool collide(std::shared_ptr<Particle>& b){
        auto overlap = [](Vector2f pos1, Vector2f pos2, double r1, double r2){
            return fabs((pos1.x - pos2.x)*(pos1.x - pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y)) <= (r1 + r2) * (r1 + r2);
        };
        double distX = radius - b->radius;
        double distY = radius - b->radius;
        double distance = sqrt( (distX*distX) + (distY*distY) );
        if (distance <= radius + b->radius) {
            return true;
        }
        return false;
    }
};


#endif //PLSDIOSITO_PARTICLE_H
