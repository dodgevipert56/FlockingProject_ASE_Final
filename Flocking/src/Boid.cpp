#include "Boid.h"
#include "ngl/Vec3.h"

Boid::Boid()
{

}

ngl::Vec3 Boid::getPosition() const
{
    return data.pos;
}

ngl::Vec3 Boid::getDirection() const
{
    return data.dir;
}

ngl::Vec3 Boid::getScale() const
{
    return data.scale;
}

ngl::Vec3 Boid::getRotation() const
{
    return data.rot;
}

ngl::Vec4 Boid::getColour() const
{
    return data.colour;
}

void Boid::setPosition(const ngl::Vec3 &_pos)
{
    data.pos = _pos;
}

void Boid::setDirection(const ngl::Vec3 &_dir)
{
    data.dir = _dir;
}

void Boid::setRotation(const ngl::Vec3 &_rot)
{
    data.rot = _rot;
}

void Boid::setScale(const ngl::Vec3 &_scl)
{
    data.scale = _scl;
}

void Boid::setColour(const ngl::Vec4 &_col)
{
    data.colour = _col;
}
