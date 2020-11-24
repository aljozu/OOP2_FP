//
// Created by lojaz on 23/11/2020.
//

#ifndef PLSDIOSITO_EVENT_H
#define PLSDIOSITO_EVENT_H
#include "Particle.h"



class event {
private:
    double time;
    std::shared_ptr<Particle> a, b;
    int countA, countB;
public:

    //creates a new event involving a and b
    event(double t, const std::shared_ptr<Particle>& a, const std::shared_ptr<Particle>& b);

    //compares times when two events will occur
    int compare_to(event &that) const;

    //checks if any collision has occurred since the creation of the event
    bool is_valid();

    //return time
    double get_time() const;

    //getters of a and b
    std::shared_ptr<Particle> get_a();
    std::shared_ptr<Particle> get_b();
};


#endif //PLSDIOSITO_EVENT_H
