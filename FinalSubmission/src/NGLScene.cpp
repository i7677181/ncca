#include "NGLScene.h"
#include <iostream>
#include <ngl/Light.h>
#include <ngl/NGLInit.h>
#include <ngl/Material.h>
#include <QColorDialog>
#include <BoidMath.h>

//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.5f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=105.0f;
//----------------------------------------------------------------------------------------------------------------------

NGLScene::NGLScene(QWidget *_parent ) : QGLWidget( _parent )
{
    char i=5;
    for(int n=0;n<=100;n++) std::cout<<"Hi Dusty\n";

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  m_origX=0;
  m_origY=0;
  m_width=this->size().width();
  m_height=this->size().height();
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  delete m_light;
  delete m_Swarm;
  delete m_boidVAO;
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Black Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // load shader and set values
  // create instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // create shader called Phong
  shader->createShaderProgram("Phong");
  // create empty frag and vert shaders
  shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
  // attach sources
  shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
  shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
  // compile shaders
  shader->compileShader("PhongVertex");
  shader->compileShader("PhongFragment");
  // addvshaders to program
  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");
  // bind shader attributes for ngl primitives
  // layout attribute 0 is the vertex data (x,y,z)
  shader->bindAttribute("Phong",0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader->bindAttribute("Phong",1,"inUV");
  // attribute 2 are the normals x,y,z
  shader->bindAttribute("Phong",2,"inNormal");
  // link the shader
  shader->linkProgramObject("Phong");
  // use shader
  (*shader)["Phong"]->use();
  // load values (temp)
 // shader->setShaderParam4f("Colour", 1.0, 0.5, 0.31,1.0);
  shader->setShaderParam4f("Colour", 0.5, 1.0, 1.0,0.0);

  m_Swarm = new Swarm(100);

  Camera();

  shader->setRegisteredUniform("viewerPos", m_camera.getEye().toVec3());
  // create a light
  ngl::Mat4 iv=m_camera.getViewMatrix();
  iv.transpose();
  m_light = new ngl::Light(ngl::Vec3(800,1000,1000),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1), ngl::LightModes::POINTLIGHT);
  m_light->setTransform(iv);
  //load light values to shader
  m_light->loadToShader("light");

  startTimer(10);
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,m_width,m_height);

  buildBoidVAO();

}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_width = _w;
  m_height = _h;
  glViewport(0,0,_w,_h);
  m_camera.setShape(45,float(_w/_h),0.05,350);
}


void NGLScene::loadMatricesToShader()
{
  // create an instance of the shader lib
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::Mat4 M, MV, MVP;
  ngl::Mat3 normalMatrix;
  M=m_transform.getMatrix();
  MV = M*m_mouseGlobalTX*m_camera.getViewMatrix();
  MVP = MV*m_camera.getProjectionMatrix();
  normalMatrix = MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);

}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // create an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  //Rotation based on the mouse position
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  // multiply rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  //draw swarm
  for(int i=0; i<m_Swarm->getSize(); ++i)
  {
      m_transform.reset();
      m_transform.setPosition(m_Swarm->m_swarm[i].getPosition());
      m_transform.addRotation( m_Swarm->m_swarm[i].getRotation());
      loadMatricesToShader();
      shader->setShaderParam4f("Colour", 0.5, 5.5, 0.31,1.0);
      drawBoid();
}

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent ( QMouseEvent * _event )
{

    if(m_rotate && _event->buttons() == Qt::LeftButton)
    {
      int diffx=_event->x()-m_origX;
      int diffy=_event->y()-m_origY;
      m_spinXFace+=(float)0.5f*diffy;
      m_spinYFace+=(float)0.5f*diffx;
      m_origX=_event->x();
      m_origY=_event->y();
      updateGL();
    }
    else if(m_translate && _event->buttons() == Qt::RightButton)
    {
      int diffX = (int)(_event->x() - m_origXPos);
      int diffY = (int)(_event->y() - m_origYPos);
      m_origXPos=_event->x();
      m_origYPos=_event->y();
      m_modelPos.m_x += INCREMENT * diffX;
      m_modelPos.m_y -= INCREMENT * diffY;
      updateGL();
    }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent (QMouseEvent * _event  )
{

  // left button rotates
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate = true;
  }
  // right button translates
  if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate = true;
  }

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent (  QMouseEvent * _event  )
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
  // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{
  // check the diff of the wheel position (0 means no change)
  if(_event->delta() > 0)
  {
    m_modelPos.m_z+=ZOOM;
  }
  else if(_event->delta() <0 )
  {
    m_modelPos.m_z-=ZOOM;
  }
  updateGL();

}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the NGLScene
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    // turn on wirframe rendering
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
    // turn off wire frame
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
    // show full screen
  case Qt::Key_F : showFullScreen(); break;
    // show windowed
  case Qt::Key_N : showNormal(); break;
}
  updateGL();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::timerEvent(QTimerEvent *_event)
{
  m_Swarm->updateSwarm();
  updateGL();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::buildBoidVAO()
{

    ngl::Vec3 verts[]=
      {
        ngl::Vec3(0,1,1),
        ngl::Vec3(0,0,-1),
        ngl::Vec3(-0.5,0,1),
        ngl::Vec3(0,1,1),
        ngl::Vec3(0,0,-1),
        ngl::Vec3(0.5,0,1),
        ngl::Vec3(0,1,1),
        ngl::Vec3(0,0,1.5),
        ngl::Vec3(-0.5,0,1),
        ngl::Vec3(0,1,1),
        ngl::Vec3(0,0,1.5),
        ngl::Vec3(0.5,0,1)

      };

      std::vector <ngl::Vec3> normals;
      ngl::Vec3 n=ngl::calcNormal(verts[2],verts[1],verts[0]);
      normals.push_back(n);
      normals.push_back(n);
      normals.push_back(n);
      n=ngl::calcNormal(verts[3],verts[4],verts[5]);
      normals.push_back(n);
      normals.push_back(n);
      normals.push_back(n);

      n=ngl::calcNormal(verts[6],verts[7],verts[8]);
      normals.push_back(n);
      normals.push_back(n);
      normals.push_back(n);

      n=ngl::calcNormal(verts[11],verts[10],verts[9]);
      normals.push_back(n);
      normals.push_back(n);
      normals.push_back(n);

      //std::cout<<"sizeof(verts) "<<sizeof(verts)<<" sizeof(ngl::Vec3) "<<sizeof(ngl::Vec3)<<"\n";
      // create a vao as a series of GL_TRIANGLES
      m_boidVAO= ngl::VertexArrayObject::createVOA(GL_TRIANGLE_STRIP);
      m_boidVAO->bind();

      // in this case we are going to set our data as the vertices above

      m_boidVAO->setData(sizeof(verts),verts[0].m_x);
      // now we set the attribute pointer to be 0 (as this matches vertIn in our shader)

      m_boidVAO->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

      m_boidVAO->setData(sizeof(verts),normals[0].m_x);
      // now we set the attribute pointer to be 2 (as this matches normal in our shader)

      m_boidVAO->setVertexAttributePointer(2,3,GL_FLOAT,0,0);

      m_boidVAO->setNumIndices(sizeof(verts)/sizeof(ngl::Vec3));

      // now unbind
      m_boidVAO->unbind();

}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::drawBoid()
{
  m_boidVAO->bind();
  m_boidVAO->draw();
  m_boidVAO->unbind();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::Camera()
{
  // create a load of cameras
  ngl::Camera cam;
  // set the different vectors for the camera positions
  ngl::Vec3 eye(0.0f,1.0f,500.0f);
  ngl::Vec3 look=0.0f;
  ngl::Vec3 up(0,1,0);

  // finally set the cameras shape and position
  cam.set(eye,look,up);
  cam.setShape(45.0f, (float)m_width/m_height, 0.05f,350.0f);

}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::createSwarm(int _cohesion, int _separation,
                       int _alignment, float _speed,
                       int _mass)
{
  m_Swarm->createSwarm(_cohesion, _separation, _alignment, _speed, _mass);
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::removeBoid()
{
  m_Swarm->removeBoid();
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::newSwarm(int _numBoids, int _cohesion, int _separation,
                        int _alignment, float _speed, int _mass)
{
  delete m_Swarm;
  m_Swarm=new Swarm(_numBoids, _cohesion, _separation,
                    _alignment, _speed, _mass);
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::setCohesion(int _cohesion)
{
  for(int i=0; i<m_Swarm->m_swarm.size(); ++i)
  {
    m_Swarm->m_swarm[i].setCWeight(_cohesion);
  }
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setSeparation(int _separation)
{
  for(int i=0; i<m_Swarm->m_swarm.size(); ++i)
  {
    m_Swarm->m_swarm[i].setSWeight(_separation);
  }
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setAlignment(int _align)
{
  for(int i=0; i<m_Swarm->m_swarm.size(); ++i)
  {
    m_Swarm->m_swarm[i].setAWeight(_align);
  }
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setSpeed(int _speed)
{
  float speed = _speed/10.0;
  for(int i=0; i<m_Swarm->m_swarm.size(); ++i)
  {
    m_Swarm->m_swarm[i].setSpeed(speed);
  }
  setFocus();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setMass(int _mass)
{
  for(int i=0; i<m_Swarm->m_swarm.size(); ++i)
  {
    m_Swarm->m_swarm[i].setMass(_mass);
  }
  setFocus();
}

void NGLScene::setSepDist(int _sepDist)
{
  for(int i=0;i<m_Swarm->m_swarm.size();++i)
  {
    m_Swarm->m_swarm[i].setSepDist(_sepDist);
  }
  setFocus();
}













