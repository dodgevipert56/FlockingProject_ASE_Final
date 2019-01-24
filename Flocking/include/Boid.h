/// \This is the header file for Boid
/// \version 1.0
/// \updated 24/01/2019

#ifndef BOID_H_
#define BOID_H_

#include <ngl/Vec3.h>
#include "WindowParams.h"
#include <ngl/Transformation.h>
#include <QOpenGLWindow>

class Boid
{
public:

    Boid();

    enum class BoidMeshType : char {CONE};
    WinParams m_win;

    ngl::Vec3 getPosition() const;
    void setPosition(const ngl::Vec3 &_pos);

    ngl::Vec3 getDirection() const;
    void setDirection(const ngl::Vec3 &_dir);

    ngl::Vec3 getScale() const;
    void setScale(const ngl::Vec3 &_scl);

    ngl::Vec3 getRotation() const;
    void setRotation(const ngl::Vec3 &_rot);

    ngl::Vec4 getColour() const;
    void setColour(const ngl::Vec4 &_col);

    struct BoidData
    {
        // all these are a pod type
        ngl::Vec3 pos;
        ngl::Vec3 dir;
        ngl::Vec3 scale;
        ngl::Vec3 rot;
        ngl::Vec4 colour;
        BoidMeshType type;

        BoidData(const ngl::Vec3 &_pos, const ngl::Vec3 &_scale, // constructor intialisation
                 const ngl::Vec3 &_rot, const ngl::Vec4 &_colour,
                 BoidMeshType _type) :
                 pos(_pos), scale(_scale), rot(_rot), colour(_colour),
                 type(_type){}
        BoidData() = default;
        BoidData(const BoidData &) = default;
        ~BoidData() = default;
    };

    BoidData data;


};


#endif // _BOID_H_
