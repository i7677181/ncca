//----------------------------------------------------------------------------------------------------------------------
/// @file Swarm.h
/// @class Swarm
/// @brief a class for creating the swarm, managing boids and their neighbours
//----------------------------------------------------------------------------------------------------------------------
#ifndef Swarm_H
#define Swarm_H

#include <stdlib.h>
#include <cmath>
#include <vector>
#include <Boid.h>
#include <Octree.h>
class Swarm
{
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor
  /// @param [in] _numBoids the number of boids in the swarm
  //----------------------------------------------------------------------------------------------------------------------
  Swarm(int _numBoids);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to set custom steering force weights, speed and mass as well as the number of boids
  /// @param [in] _numBoids the number of boids in the swarm
  /// @param [in] _cohesion the custom cohesion force weight to set
  /// @param [in] _separation the custom spearation force weight to set
  /// @param [in] _alignment the custom alignment force weight to set
  /// @param [in] _speed the custom speed value to be set
  /// @param [in] _mass the custom mass value to be set
  //----------------------------------------------------------------------------------------------------------------------
  Swarm(int _numBoids, int _cohesion, int _separation, int _alignment, float _speed, int _mass);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor
  //----------------------------------------------------------------------------------------------------------------------
  ~Swarm();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add a boid to the swarm
  /// @param [in] _cohesion the cohesion force weight to set to the boid
  /// @param [in] _separation the spearation force weight to set to the boid
  /// @param [in] _alignment the alignment force weight to set to the boid
  /// @param [in] _speed the speed value to set to the boid
  /// @param [in] _mass the mass value to set to the boid
  //----------------------------------------------------------------------------------------------------------------------
  void createSwarm(int _cohesion, int _separation, int _alignment, float _speed, int _mass);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to remove a boid from the swarm
  //----------------------------------------------------------------------------------------------------------------------
  void removeBoid();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to st the boid position
  /// @param [in] _id the id of the boid to set neighbours to
  //----------------------------------------------------------------------------------------------------------------------
  void setNeighbours(int _id);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to return the size of the swarm
  //----------------------------------------------------------------------------------------------------------------------
  int getSize();
  /// @brief method to update the swarm, neighbours,
  /// collisions and positions of the boids
  void updateSwarm();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief vector to contain all boids within the swarm
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Boid> m_swarm;
  //----------------------------------------------------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to update the octree. deletes the previous octree,
  /// creates a new one and populates it with the new data points
  //----------------------------------------------------------------------------------------------------------------------
  void updateOctree();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a pointer to the octree class for managing neighbours
  //----------------------------------------------------------------------------------------------------------------------
  Octree *m_octree;
};

#endif // swarm_H
