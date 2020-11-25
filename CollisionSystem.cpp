//
// Created by lojaz on 24/11/2020.
//
#include <iostream>
#include "CollisionSystem.h"




void CollisionSystem::predict(std::shared_ptr<Particle> a, double limit) {
    if (a == nullptr) return;

    // particle-particle collisions
    for (size_t i = 0; i < particles.size(); i++) {
        double dt = a->time_to_hit(particles[i]);
        if (t + dt <= limit)
            pq.push(event(t + dt, a, particles[i]));
    }

    // particle-wall collisions
    double dtX = a->time_to_hit_vertical_wall();
    double dtY = a->time_to_hit_horizontal_wall();
    if (t + dtX <= limit) pq.push(event(t + dtX, a, nullptr));
    if (t + dtY <= limit) pq.push(event(t + dtY, nullptr, a));
}

void CollisionSystem::redraw(double limit, RenderWindow &window) {
    particles.drawContainer(window);
    sf::Time t3 = sf::seconds(0.2);
    if (t < limit) {
        pq.push(event(t + 1.0 / HZ, nullptr, nullptr));
    }
}

void CollisionSystem::simulate(double limit, RenderWindow &window) {
    //pq = std::priority_queue<event, std::vector<event>, Compare_Time>();
    for (int i = 0; i < particles.size(); i++) {
        predict(particles[i], limit);
    }
    //pq.push(event(0, nullptr, nullptr));

    while (!pq.empty()){
        event e = pq.top();

        if (!e.is_valid()) continue;
        std::shared_ptr<Particle> a = e.get_a();
        std::shared_ptr<Particle> b = e.get_b();

        for (int i = 0; i < particles.size(); i++) {
            std::cout << e.get_time() - t;
            particles[i]->move(e.get_time() - t);
        }


        if      (a != nullptr && b != nullptr) a->bounce_off(b);              // particle-particle collision
        else if (a != nullptr && b == nullptr) a->bounce_off_vertical_wall();   // particle-wall collision
        else if (a == nullptr && b != nullptr) b->bounce_off_horizontal_wall(); // particle-wall collision
        else if (a == nullptr && b == nullptr) redraw(limit, window);               // redraw event

        predict(a, limit);
        predict(b, limit);
    }

}

CollisionSystem::CollisionSystem(const particles_container& parts) {
    particles = parts;
}


