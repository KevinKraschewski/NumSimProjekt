/*
 * Copyright (C) 2015   Malte Brunn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "compute.hpp"

/// Creates a compute instance with given geometry and parameter
Compute::Compute(const Geometry *geom, const Parameter *param){
  // hier fehlt noch was
}
/// Deletes all grids
Compute::~Compute(){
  // hier fehlt noch was
}

/// Execute one time step of the fluid simulation (with or without debug info)
// @ param printInfo print information about current solver state (residual
// etc.)
void Compute::TimeStep(bool printInfo){
  // hier fehlt noch was
}

/// Returns the simulated time in total
const real_t Compute::&GetTime() const{
  return _t;
}

/// Returns the pointer to U
const Grid Compute::*GetU() const{
  return _u;
}

/// Returns the pointer to V
const Grid Compute::*GetV() const{
  return _v;
}

/// Returns the pointer to P
const Grid Compute::*GetP() const{
  return _p;
}

/// Returns the pointer to RHS
const Grid Compute::*GetRHS() const{
  return _rhs;
}

/// Computes and returns the absolute velocity
const Grid Compute::*GetVelocity(){
  // hier fehlt noch was
  return _F; //falsch
}

/// Computes and returns the vorticity
const Grid Compute::*GetVorticity(){
  // hier fehlt noch was
  return _F; //falsch
}

/// Computes and returns the stream line values
const Grid Compute::*GetStream(){
  // hier fehlt noch was
  return _F; //falsch
}


  // current timestep
  //real_t _t;

  // donor-cell diffusion condition (p. 27)
  //real_t _dtlimit;

  // limit for residual
  //real_t _epslimit;

  // velocities
  //Grid *_u;
  //Grid *_v;

  // pressure
  //Grid *_p;

  // prel. vel
  //Grid *_F;
  //Grid *_G;

  // right-hand side
  //Grid *_rhs;

  // container for interpolating whichever values
  //Grid *_tmp;

  //Solver *_solver;

  //const Geometry *_geom;
  //const Parameter *_param;

  /// Compute the new velocites u,v
  void Compute::NewVelocities(const real_t &dt){
    // hier fehlt noch was
  }
  
  /// Compute the temporary velocites F,G
  void Compute::MomentumEqu(const real_t &dt){
    // hier fehlt noch was
  }
  
  /// Compute the RHS of the poisson equation
  void Compute::RHS(const real_t &dt){
    // hier fehlt noch was
  }
