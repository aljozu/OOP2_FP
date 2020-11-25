//
// Created by lojaz on 22/11/2020.
//



#include "Particle.h"
const double infinity = std::numeric_limits<double>::max();
std::random_device dev;
template<class T>
double Rand(T first, T last) {
    std::default_random_engine eng(dev());
    std::uniform_real_distribution<double> dis(first, last);
    return dis(eng);
}

Particle::Particle(Vector2f _position, Vector2f _velocity, double _radius, double _mass, bool _sick) {
    position = _position;
    velocity = _velocity;
    radius = _radius;
    mass = _mass;
    sick = _sick;

    if(sick) color = sf::Color::Green;
    else color = sf::Color::Red;

    //giving values to the particle
    particle.setPosition(position);
    particle.setRadius(radius);
    particle.setFillColor(color);
    particle.setOutlineColor(sf::Color::Black);
}

Particle::Particle(bool sick) {
    position.x = Rand(0.0, 1200.0);
    position.y = Rand(0.0, 800.0);
    velocity.x = Rand(-0.005, 0.005);
    velocity.y = Rand(-0.005, 0.005);
    radius = 2.0;
    mass = 0.5;

    if(sick) color = sf::Color::Green;
    else color = sf::Color::Red;

    //giving values to the particle
    particle.setPosition(position);
    particle.setRadius(radius);
    particle.setFillColor(color);
    particle.setOutlineColor(sf::Color::Black);
}

void Particle::move(double dt) {
    position.x += velocity.x * dt;      // d = v *t
    position.y += velocity.y * dt;
    particle.setPosition(position.x, position.y);
}

void Particle::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) const {
    renderTarget.draw(particle);
}

int Particle::_count() {
    return count;
}

double Particle::time_to_hit(std::shared_ptr<Particle> that) {
    //if(this == that) return infinity;
    double dx = that->position.x - position.x;
    double dy  = that->position.y - position.y;
    double dvx = that->velocity.x - velocity.x;
    double dvy = that->velocity.y - velocity.y;
    double dvdr = dx*dvx + dy*dvy;
    if (dvdr > 0) return infinity;
    double dvdv = dvx*dvx + dvy*dvy;
    if (dvdv == 0) return infinity;
    double drdr = dx*dx + dy*dy;
    double sigma = radius + that->radius;
    double d = (dvdr*dvdr) - dvdv * (drdr - sigma*sigma);
    if (d < 0) return infinity;
    return -(dvdr + sqrt(d)) / dvdv;
}

double Particle::time_to_hit_vertical_wall() {
    if      (velocity.x > 0) return (1.0 - position.x - radius) / velocity.x;
    else if (velocity.x < 0) return (radius - position.x) / velocity.x;
    else  return infinity;
}

double Particle::time_to_hit_horizontal_wall() {
    if      (velocity.y > 0) return (1.0 - position.y - radius) / velocity.y;
    else if (velocity.y < 0) return (radius - position.y) / velocity.y;
    else return infinity;
}

void Particle::bounce_off(std::shared_ptr<Particle>& that) {
    double dx  = that->position.x - position.x;
    double dy  = that->position.y - position.y;
    double dvx = that->velocity.x - velocity.x;
    double dvy = that->velocity.y - velocity.y;
    double dvdr = dx*dvx + dy*dvy;             // dv dot dr
    double dist = radius + that->radius;   // distance between particle centers at collison

    // magnitude of normal force
    double magnitude = 2 * mass * that->mass * dvdr / ((mass + that->mass) * dist);

    // normal force, and in x and y directions
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    // update velocities according to normal force
    velocity.x += fx / mass;
    velocity.y += fy / mass;
    that->velocity.x -= fx / that->mass;
    that->velocity.y -= fy / that->mass;

    // update collision counts
    count++;
    that->count++;
}

void Particle::bounce_off_vertical_wall() {
    velocity.x = -velocity.x;
    count++;
}

void Particle::bounce_off_horizontal_wall() {
    velocity.y = -velocity.y;
    count++;
}

double Particle::kinetic_energy() {
    return 0.5 * mass * (velocity.x*velocity.x + velocity.y*velocity.y);
}

void Particle::set_id(size_t _id) {
    id = _id;
}

Particle::Particle() {

}

double Particle::get_posx() {return position.x;}

double Particle::get_posy() {return position.y;}

void Particle::set_velx(double v) {velocity.x = v;}

void Particle::set_vely(double v) {velocity.y = v;}

double Particle::get_velx() {return velocity.x;}

double Particle::get_vely() {return velocity.y;}

bool Particle::collide(std::shared_ptr<Particle> &b) {
    return fabs((position.x - b->position.x)*(position.x - b->position.x)+
                                (position.y-b->position.y)*(position.y-b->position.y)) <= (radius + b->radius) * (radius + b->radius);
}

Vector2f Particle::get_position() {
    return position;
}

void Particle::set_position(Vector2f new_pos) {
    position = new_pos;
}

double Particle::get_radius() {
    return radius;
}

void Particle::set_posx(float newx) {
    position.x = newx;
}

void Particle::set_posy(float newy) {
    position.y = newy;
}

double Particle::magnitude(std::shared_ptr<Particle> &that) {
    double dx  = that->position.x - position.x;
    double dy  = that->position.y - position.y;
    double dvx = that->velocity.x - velocity.x;
    double dvy = that->velocity.y - velocity.y;
    double dvdr = dx*dvx + dy*dvy;             // dv dot dr
    double dist = radius + that->radius;   // distance between particle centers at collison

    // magnitude of normal force
    double magnitude = 2 * mass * that->mass * dvdr / ((mass + that->mass) * dist);
    return magnitude;
}

double Particle::get_mass() {
    return mass;
}

Particle::~Particle() = default;










