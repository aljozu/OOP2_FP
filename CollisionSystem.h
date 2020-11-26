//
// Created by lojaz on 24/11/2020.
//

#ifndef PLSDIOSITO_COLLISIONSYSTEM_H
#define PLSDIOSITO_COLLISIONSYSTEM_H
#define HZ 0.5

#include "Particle.h"
#include "particles_container.h"
#include "event.h"

struct Compare_Time{
    bool operator()(const event& e1, const event& e2) const
    {
        return e1.get_time() < e1.get_time();
    }
};

class CollisionSystem {
private:
    std::priority_queue<event, std::vector<event>,Compare_Time> pq; //priority queue order by the time in which an event is gonna occur
    double t = 0.0;
    particles_container particles;
public:
    //constructor
    explicit CollisionSystem(const particles_container& parts);

    //funciton that updates the priority queue with the events that happens to the particle
    void predict(std::shared_ptr<Particle> a, double limit);

    //function that redraws each particle after they are update
    void redraw(double limit, RenderWindow &window);

    //simulates the system of particles for the specified amount of time
    void simulate(double limit, RenderWindow &window);
};


#endif //PLSDIOSITO_COLLISIONSYSTEM_H
