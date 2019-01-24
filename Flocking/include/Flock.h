/// \This is the header file for Flock
/// \version 1.0
/// \updated 24/01/2019


#ifndef FLOCK_H
#define FLOCK_H
#include "Boid.h"

class Flock
{
public:
    Flock();
    std::vector<Boid::BoidData> m_boids; // making object or instance
    std::vector<std::vector<Boid::BoidData *>> m_boidCollection;

    void lookAt();
    void allignment();
    void allignmentRandom();
    void separation();
    void cohesion();
    void limit();
    void prune();
};

#endif // _FLOCK_H
