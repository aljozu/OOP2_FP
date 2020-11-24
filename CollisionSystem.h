//
// Created by lojaz on 24/11/2020.
//

#ifndef PLSDIOSITO_COLLISIONSYSTEM_H
#define PLSDIOSITO_COLLISIONSYSTEM_H
#define HZ 0.5
#include <queue>
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
    std::priority_queue<event, std::vector<event>,Compare_Time> pq;
    double t = 0.0;
    particles_container particles;
public:
    explicit CollisionSystem(const particles_container& parts);
    void predict(const std::shared_ptr<Particle>& a, double limit);
    void redraw(double limit, RenderWindow &window);
    void simulate(double limit, RenderWindow &window);
};


#endif //PLSDIOSITO_COLLISIONSYSTEM_H
