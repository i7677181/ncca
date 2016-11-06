#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include "Boid.h"
#include "BoidMath.h"

Boid::Boid(int _id)
{
  //set forces to 0
  setPos(0.0, 0.0, 0.0);
  m_position.m_z = 0.0;
  m_velocity.set(1.0, 0.0, 0.0);
  m_reposition.set(0,0,0);
  m_id=_id;
  //set weights
  m_alignmentWeight=50;
  m_separationWeight=100;
  m_cohesionWeight=200;
  m_speed=5.5f;
  m_mass=250;
  m_viewRange =10;
  m_avoidWeight = 100;
  m_boundRadius=5;
  m_collisionPos =0; //position of collision vec
  m_searchRad = 10;
  m_separationDistance = 10;

}

Boid::~Boid()
{

}

void Boid::setPos(float _x, float _y, float _z)
{
  m_position.set(_x,_y,_z);
}

void Boid::setNeighbour(Boid *boid)
{

    m_neighbours.push_back(boid);

}

void Boid::clearNeighbour()
{
  //clear the m_neighbours vector
  m_neighbours.clear();
}

void Boid::setVelocity(float _x, float _y, float _z)
{
  m_velocity.set(_x,_y,_z);
}

void Boid::setSWeight(int _separationWeight)
{
  m_separationWeight = _separationWeight;
}

void Boid::setCWeight(int _cohesionWeight)
{
  m_cohesionWeight = _cohesionWeight;
}

void Boid::setAWeight(int _alignWeight)
{
  m_alignmentWeight = _alignWeight;
}

void Boid::setMass(int _mass)
{
  m_mass = _mass;
}
void Boid::setSpeed(float _speed)
{
  //set minimum speed
  m_setSpeed=_speed;
  m_speed=m_setSpeed;
}


void Boid::setCohesion()
{

  if(m_neighbours.size()>0)
  {
    m_cohesion = -(m_position+m_neighbours.size())/2;
    if(m_cohesion.length()!=0)
    m_cohesion.normalize();
  }
  // if the boid has no neighbours then has no cohesion force
  else m_cohesion.set(0,0,0);
}

void Boid::setAlignment()
{
  // alignment force is calculated by averaging the boid's neighbours's velocities
  if(m_neighbours.size()>0)
  {
    for(int i=0;i<m_neighbours.size();++i)
    {
      m_alignment+=m_neighbours[i]->getVelocity();
    }
    m_alignment *= m_neighbours.size();
    if(m_alignment.length()!=0)
    {
      m_alignment.normalize();
    }
  }
  // if the boid has no neighbours it has no alignment force
  else
    m_alignment.set(0,0,0);
}

void Boid::setSeparation()
{
  // separation is calculated by taking a vector from each neighbours position to the boid's
  // position and averaging them.
  m_separation.set(0,0,0);
  for(int i=0;i<m_neighbours.size();++i)
  {
    // if the neighbour is within the boid's separation radius then add a vector from the
    // neighbour to the boid's position and separation vector.
    if(BoidMath::distance(m_position, m_neighbours[i]->getPosition())>m_separationDistance)
    {
      ngl::Vec3 pos(m_neighbours[i]->getPosition()); //current position of neighbour
      ngl::Vec3 dir = (m_position-pos); //the direction
      m_separation += dir; //add direction to separation
    }

  }
  if(m_neighbours.size()>0)
  {
    m_separation /= m_neighbours.size();
  }
  if(m_separation.length()!=0)
  {
    m_separation.normalize();
  }
}

void Boid::setAvoid()
{
  //check if boids collide with eachother
  for(int i=0; i<m_neighbours.size();++i)
  {
    Collision(m_neighbours[i]->getPosition(), m_neighbours[i]->getRadius());
  }
  if(m_velocity.length()!=0)
  {
    m_velocity.normalize();
  }
  // if there is a collision, calculate an avoidance force as a vector
  // from the collision position to the ahead vector
  m_avoid=(0,0,0);
    //  ngl::Vec3 ahead(m_position + m_velocity * m_viewRange * m_speed);
  if(m_collisionPos != 0)
  {
    m_avoid=((m_position+m_velocity*(m_viewRange*2)*(m_speed/2))-m_collisionPos);
    if(m_avoid.length()!=0)
    {
      m_avoid.normalize();
    }
  }
  else
  {
    m_avoid*=0;
  }
  m_collisionPos = 0;
}

void Boid::setReposition(ngl::Vec3 _reposition)
{
  // the reposition force is calculated as a vector from the reposition position
  // to the boid
  if(BoidMath::distance(_reposition,m_position)<50)
  {
    m_reposition=-(_reposition-m_position);
    if(m_reposition.length()!=0)
    {
      m_reposition.normalize();
    }
  }
}

void Boid::repositionBounds()
{
  // if a boid raoms outside of the BBox,it repositions itself to turn around
  if(m_position.m_x<=-150 || m_position.m_x>=150)
  {
    m_reposition.m_x-=(m_position.m_x/2);
  }
  if(m_position.m_y<=-150 || m_position.m_y>=150)
  {
    m_reposition.m_y-=(m_position.m_y/2);
  }
  if(m_position.m_z<=-150 || m_position.m_z>=150)
  {
    m_reposition.m_z-=(m_position.m_z/2);
  }
  // if a boid wanders too far out of BBox range,it spawns at it's origin(0,0,0)

  if(m_position.m_x<=-250 || m_position.m_x>=250)
  {
    m_reposition.set(0,0,0);
    m_position.m_x=m_reposition.m_x;
  }
  if(m_position.m_y<=-250 || m_position.m_y>=250)
  {
      m_reposition.set(0,0,0);
      m_position.m_y=-(m_reposition.m_y);
  }
  if(m_position.m_z<=-250 || m_position.m_z>=250)
  {
      m_reposition.set(0,0,0);
    m_position.m_z=-(m_reposition.m_z);
  }

}

void Boid::setDirection()
{
m_direction.set(0,0,0);
// scale by avoid weight
m_avoid*=m_avoidWeight;
// the direction is calculated by the reposition and avoidance
m_direction=m_reposition+m_avoid;
// scale the behaviour forces by their weights
m_separation*=m_separationWeight;
m_alignment*=m_alignmentWeight;
m_cohesion*=m_cohesionWeight;

// set the direction by combining the weighted forces
m_direction+=m_separation+m_cohesion+m_alignment+m_avoid+m_reposition;

}

void Boid::setSteering()
{
  // set a steering vector from the current velocity to the dir
  m_steering = m_direction-m_velocity;
  if(m_steering.length()!=0)
    m_steering.normalize();
}

void Boid::updatePosition()
{
  // update the velocity by adding the steering vector divided by the mass
  m_velocity = m_velocity+(m_steering/m_mass);
  // scale it by the speed
  if(m_velocity.length()!=0)
  {
    m_velocity.normalize();
    m_velocity*=m_speed;
  }
  // add the velocity to the current position to update it
  m_position = m_position+m_velocity;
}


void Boid::setRotate()
{
  m_yaw = atan2(m_velocity.m_x,m_velocity.m_z)*180/M_PI+180;
  m_pitch = atan2(m_velocity.m_y,sqrt(m_velocity.m_x*m_velocity.m_x+m_velocity.m_z*m_velocity.m_z))*180/M_PI;
}
    //combine all movement methods
    void Boid::move()
    {

    m_reposition.set(0,0,0);
    //find neighbours

    if(m_neighbours.size()<=1 && m_searchRad<350)
    {
    m_searchRad*=2;
    }

    if(m_searchRad<=!10 && m_neighbours.size()>=5)
    {
    m_searchRad/=2;
    }
    //set behaviour
    setSeparation();
    setAlignment();
    setCohesion();
    //collision control
    setAvoid();
    repositionBounds();
    //calculate new direction if a collision has occured
    setDirection();
    setSteering();
    //update
    updatePosition();
    setRotate();
    }

void Boid::Collision(ngl::Vec3 _pos, float _rad)
{
  ngl::Vec3 ahead(m_position + m_velocity * m_viewRange * m_speed);
  bool collision = BoidMath::collisionDetect(ahead, _pos, m_position, _rad);
  //if a a collision is detected
  if(collision==true  && (m_collisionPos==0 || BoidMath::distance(m_position, _pos) < BoidMath::distance(m_position, m_collisionPos)))
  {
    m_collisionPos=_pos;
  }
}

