#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h> // methods to create primitives - torus, sphere, and built in prims
#include <ngl/ShaderLib.h> // another singleton class, ways of managing itself
#include <ngl/NGLStream.h> // implements all ostream operators, for printing
#include <iostream>
#include <ngl/Random.h>
#include <ngl/fmt/format.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleVAO.h>
#include <ngl/NGLMessage.h>


NGLScene::NGLScene(size_t _numMeshes)
{
    m_flock.cohesion();

    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    setTitle(fmt::format("Flocking NGL Num Boids {0}", _numMeshes).c_str()); //fmt - lib python and c style formats with place holder {0} or %d stuff
    m_flock.m_boids.resize(_numMeshes);
    spawnBoids();
    m_flock.m_boidCollection.resize(1); // only one object "CONE" by default needed was 4
    updateCollection();
    startTimer(10);
}

void NGLScene::addBoidClick(Boid::BoidMeshType cone)
{

    ngl::Random *rng = ngl::Random::instance();
    Boid::BoidData boid;

    boid.pos = rng->getRandomPoint(60, 60, 60);
    boid.rot.m_y =rng->randomPositiveNumber(360.0f);
    boid.scale.set(1.0f, 1.0f, 1.0f);
    boid.colour = rng->getRandomColour4();
    boid.type = cone;
    m_flock.m_boids.push_back(boid);
}

void NGLScene::spawnBoids() // not const becuz it a mutate
{
    ngl::Random *rng = ngl::Random::instance(); // rand class
    for (auto &m : m_flock.m_boids) // its going to mutate the value in there and need a copy
    {
        m.pos = rng->getRandomPoint(30, 30, 30); // on a plane the position with given range 40 in this case

        m.rot.m_y = rng->randomPositiveNumber(360.0f); // 0 to 360
        m.scale.set(1.0f, 1.0f, 1.0f);
        m.colour = rng->getRandomColour4();
        int type = static_cast<int>(rng->randomPositiveNumber(1));
        switch(type)
        {
            case 0 : m.type = Boid::BoidMeshType::CONE; break;
        }
    }
}

NGLScene::~NGLScene()
{
    std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w , int _h)
{
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
    m_project = ngl::perspective(50.0f, static_cast<float>(_w)/_h,
                               0.5f, 10000.0f); //FOV , last are near and far clipping planes
}

constexpr auto *ColourShader = "ColourShader"; // In compile time replaced

void NGLScene::initializeGL()
{
    // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
    // be done once we have a valid GL context but before we call any GL commands. If we dont do
    // this everything will crash
    ngl::NGLInit::instance();
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);			   // Grey Background- BACKGROUND
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);
    ngl::VAOPrimitives::instance()->createCone("cone", 1.0f, 2.5, 10, 1); // initialise cone with descriptions
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader->loadShader(ColourShader, "shaders/ColourVertex.glsl", //loading the shaders from the ones we created
                      "shaders/ColourFragment.glsl");


    m_view = ngl::lookAt({0.0f, 200.0f, 50.0f},  //gen a func to simulate glu lookat, 4*4 matrix
                       ngl::Vec3::zero(),
                       ngl::Vec3::up());

    m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_LINES); // created Vertex array objects

    ///render text
    m_text.reset(new  ngl::Text(QFont("Arial",18)));
    m_text->setScreenSize(this->size().width(),this->size().height());
    m_text->setColour(0.0,0.0,0.0);
}

void NGLScene::loadMatrixToShader(const ngl::Mat4 &_tx, const ngl::Vec4 &_colour) // getMatrix is a const cant be mutable or something like that
{
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    shader->use(ColourShader); //activate shader

    shader->setUniform("MVP", m_project*m_view*_tx); // using proj and view identity matrices from NGLScene - draw objects

    shader->setUniform("vertColour", _colour); // give color
}

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,m_win.width,m_win.height);

    ngl::Mat4 rotX;
    ngl::Mat4 rotY;
    ngl::Mat4 mouseRotation;
    rotX.rotateX(m_win.spinXFace); // rot around x axis and in angles according to mouse press down
    rotY.rotateY(m_win.spinYFace);
    mouseRotation = rotY*rotX;

    ngl::Transformation tx;
    auto *prim = ngl::VAOPrimitives::instance();
    for(auto m : m_flock.m_boids)
    {
        tx.setPosition(m.pos);  // set Position for paint
        tx.setRotation(m.rot);
        tx.setScale(m.scale);
        loadMatrixToShader(mouseRotation*tx.getMatrix(), m.colour);

        switch(m.type)
        {
            case Boid::BoidMeshType::CONE : prim->draw("cone"); break;
        }
    }
    m_text->renderText(10,10,"'up arrow' for Separation, 'down arrow' for Cohesion, Press and hold '<-' or '->' for allignment and allignment random, 'Space' to add Boids, 'C' to Reset");
}


void NGLScene::keyPressEvent(QKeyEvent *_event)
{

  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    case Qt::Key_Space : addBoidClick(Boid::BoidMeshType::CONE); break;
       // m_win.spinXFace=0;
       // m_win.spinYFace=0;
       // m_modelPos.set(ngl::Vec3::zero()); break;

    case Qt::Key_C : if(m_flock.m_boids.size()<=0) m_flock.m_boids.resize(100); spawnBoids(); break; // draw each time, even after all gone
    case Qt::Key_Down : m_flock.cohesion(); break;
    case Qt::Key_Up : m_flock.separation(); break;
    case Qt::Key_Left : m_flock.allignment(); break;
    case Qt::Key_Right : m_flock.allignmentRandom(); break;

    default : break;
    }

    update();
}

void NGLScene::updateCollection()
{
    for(auto &c : m_flock.m_boidCollection)
        c.clear();

    for(auto &m : m_flock.m_boids) // need memory otherwise we dont get a draw - not a copy
    {
        switch(m.type)
        {
            case Boid::BoidMeshType::CONE :
                m_flock.m_boidCollection[0].push_back(&m);
                break;
        }
    }
}

//All the Movement happens here
void NGLScene::timerEvent(QTimerEvent *_event)
{
    updateCollection();
    m_flock.allignment();
    m_flock.lookAt();

    update();
}
