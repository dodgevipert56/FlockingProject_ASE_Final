#include "Flock.h"
#include "NGLScene.h"
#include <ngl/Random.h>

Flock::Flock()
{
}

void Flock::cohesion()
{
    ngl::Vec3 center;

    for(size_t i=0; i<m_boidCollection.size(); ++i)
    {
        for(auto m:m_boidCollection[i]) // all of the cones
        {
            center += m->pos;
        }

        center /= m_boidCollection[i].size(); // doing this gives the center by averaging

        for(auto &m:m_boidCollection[i])
        {
            m->dir =center - m->pos;
            m->dir.normalize();
            m->pos += m->dir;
        }
    }
}

void Flock::lookAt()
{
    const float pi = 3.14f;


    for(size_t i=0; i<m_boidCollection.size(); ++i)
    {
        for(auto &m:m_boidCollection[i])
        {
            auto yaw = std::atan2(m->dir.m_x, m->dir.m_z); //finding the look at angle based on the direction headed
            yaw = yaw * (180.0f/pi);

            float xzPlane = sqrtf((m->dir.m_x * m->dir.m_x) + (m->dir.m_z * m->dir.m_z)); //getting the xz plane

            auto pitch = std::atan( m->dir.m_y / xzPlane);
            pitch = pitch * (180.0f/pi);

            m->rot.m_y = yaw;    //------- YAW
            m->rot.m_x = -pitch; //------- PITCH
        }
    }
}

void Flock::separation()
{

    for(size_t i=0; i<m_boidCollection.size(); ++i)
    {
        for(auto &m:m_boidCollection[i])
        {
            m->dir.set(m[i].pos - m[i+1].pos);
            m->dir.normalize();
            if(m->dir.length() > 0.0f)
                m->pos += m->dir;
        }
    }
}


void Flock::allignmentRandom()
{
    ngl::Random *rng = ngl::Random::instance();

    for(size_t i=0; i<m_boidCollection.size(); ++i)
    {
        for(auto &m:m_boidCollection[i])
        {
            m->dir += rng->getRandomPoint(0.1f, 0.1f, 0.1f);
            m->dir.normalize();
            m->pos += m->dir;
        }
    }
}

void Flock::allignment()
{
    ngl::Random *rng = ngl::Random::instance();

    for(size_t i=0; i<m_boidCollection.size(); ++i)
    {
        ngl::Vec3 rndDir = rng->getRandomPoint(0.1f, 0.1f, 0.1f);
        for(auto &m:m_boidCollection[i])
        {
            m->dir += rndDir;
            m->dir.normalize();
            m->pos += m->dir;
        }
    }
}

