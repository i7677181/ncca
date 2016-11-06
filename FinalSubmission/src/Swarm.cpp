#include "Swarm.h"
#include "Boid.h"
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <BoidMath.h>

Swarm::Swarm(int _numBoids)
{
  for(int i=0; i < _numBoids; i++)
  {
    createSwarm(200, 200, 50,5.5, 15);
  }
  m_octree=new Octree(ngl::Vec3(0,0,0), 150, 6);
}

Swarm::Swarm(int _numBoids, int _cohesion, int _separation, int _alignment, float _speed, int _mass)
{
  for(int i=0; i < _numBoids; i++)
  {
    createSwarm(_cohesion, _separation, _alignment, _speed, _mass);
  }
  m_octree=new Octree(ngl::Vec3(0,0,0), 150, 6);
}

Swarm::~Swarm()
{
  delete m_octree;
}

void Swarm::createSwarm(int _cohesion, int _separation, int _alignment, float _speed, int _mass)
{
  // randomise the velocity and set initial position to the origin
  float min = -1.0, max = 1.0;
  int r;
  float fraction;
  r = rand();
  fraction = ((float) r / RAND_MAX) * (max - min);
  float x = min + fraction;
  r = rand();
  fraction = ((float) r / RAND_MAX) * (max - min);
  float y = min + fraction;
  r = rand();
  fraction = ((float) r / RAND_MAX) * (max - min);
  float z =min + fraction;
  int id = m_swarm.size() + 1;
  Boid boid(id); //current boid's id
  boid.setPos(0,0,0);
  // set the steering force weights from user
  boid.setCWeight(_cohesion);
  boid.setSWeight(_separation);
  boid.setAWeight(_alignment);
  boid.setSpeed(_speed);
  boid.setMass(_mass);
  // set the randomised velocity
  boid.setVelocity(x,y,z);
  // add the boid to the swarm array
  m_swarm.push_back(boid);
}

void Swarm::removeBoid()
{
  if(m_swarm.size()>0)
  {
    m_swarm.erase(m_swarm.end()-1);
  }
}

int Swarm::getSize()
{
  return m_swarm.size();
}

void Swarm::updateOctree()
{
  // delete the old octree
  delete m_octree;
  // create a new octree
  m_octree=new Octree(ngl::Vec3(0,0,0), 150, 6);
  // populate the new octree with all the new data points
  ngl::Vec4 dataPoint;
  for(int i=0;i<m_swarm.size();++i)
  {
    dataPoint.set(m_swarm[i].getPosition().m_x,m_swarm[i].getPosition().m_y,m_swarm[i].getPosition().m_z,m_swarm[i].getId());
    m_octree->insert(dataPoint);
  }
}

void Swarm::setNeighbours(int _id)
{
  // centre of sphere to check is the position of the boid who's
  // neighbours are being set
  ngl::Vec3 centre = (m_swarm[_id].getPosition());
  // boid's search radius
  int rad = m_swarm[_id].getSearchRad();
  // clear the old neighbours
  m_swarm[_id].clearNeighbour();
  // search the octree for boids in the search sphere
  m_octree->getPointsInsideSphere(centre, rad);
  for(int i=0;i<m_octree->m_resultsData.size();++i)
  {
    // the neighbour id is the 4th element of the data vector
    float id = (m_octree->m_resultsData[i].m_w);
    // set the boid to be a neighbour only if it is not the current boid
    if(id!=m_swarm[_id].getId())
    {
      m_swarm[_id].setNeighbour(&m_swarm[(int)id-1]);
    }
  }
}

void Swarm::updateSwarm()
{
  // update octree
  updateOctree();
  // for each boid
  for(int i=0; i<m_swarm.size();++i)
  {
    // clear the octree results array
    m_octree->clearResults();
    // set the neighbours to the boud
    setNeighbours(i);
    // move the boid
    m_swarm[i].move();

  }

}
