//
// Created by lojaz on 23/11/2020.
//

#include "event.h"
#include <cmath>

inline bool compare(double a1, double a2) {
    return fabs(a1 - a2) < fabs(a2) * std::numeric_limits<double>::epsilon();
}

event::event(double t, const std::shared_ptr<Particle>& _a, const std::shared_ptr<Particle>& _b) {
    time = t;
    a = _a;
    b = _b;
    if (_a != nullptr) countA = a->_count();
    else countA = -1;
    if (_b != nullptr) countB = b->_count();
    else countB = -1;
}



int event::compare_to(event &that) const {
    return compare(time, that.time);
}

bool event::is_valid() {
    if (a != nullptr && a->_count() != countA) return false;
    if (b != nullptr && b->_count() != countB) return false;
    return true;
}

double event::get_time() const {
    return time;
}

std::shared_ptr<Particle> event::get_a() {
    return a;
}

std::shared_ptr<Particle> event::get_b() {
    return b;
}

