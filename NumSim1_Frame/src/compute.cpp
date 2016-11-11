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

#include <math.h>
#include <iostream>
#include "geometry.hpp"
#include "grid.hpp"
#include "parameter.hpp"
#include "compute.hpp"
#include "solver.hpp"
#include "iterator.hpp"

/// Creates a compute instance with given geometry and parameter
Compute::Compute(const Geometry *geom, const Parameter *param){
  _t = 0;//param->Dt();
  _geom  = geom;
  _param = param;
  _dtlimit = param->Tau()*(param->Re()/2)*(pow(_geom->Mesh()[0],2) * pow(_geom->Mesh()[1],2))/(2*(pow(_geom->Mesh()[0],2) + pow(_geom->Mesh()[1],2)));
  _epslimit = _param->Eps()*_param->Eps()*_geom->Size()[0]*_geom->Size()[1]; //N entspricht sizex*sizey, quadriertes eps spart Wurzel für Residuum
  _u = new Grid(_geom, {_geom->Mesh()[0]/2, 0.0});
  _u->Initialize(0.0);
  _v = new Grid(_geom, {0.0, _geom->Mesh()[1]/2});
  _v->Initialize(0.0);
  _p = new Grid(_geom);
  _p->Initialize(0.0);
  _F = new Grid(_geom, {_geom->Mesh()[0]/2, 0.0});
  _F->Initialize(0.0); // für homogene Neumann-Randbedingungen in p 
  _G = new Grid(_geom, {0.0, _geom->Mesh()[1]/2});
  _G->Initialize(0.0); // für homogene Neumann-Randbedingungen in p 
  _rhs = new Grid(_geom);
  _rhs->Initialize(0.0);
  _tmp = new Grid(_geom);
  _tmp->Initialize(0.0);
  _solver = new SOR(_geom, _param->Omega());
}
/// Deletes all grids
Compute::~Compute(){
  
}

/// Execute one time step of the fluid simulation (with or without debug info)
// @ param printInfo print information about current solver state (residual
// etc.)
void Compute::TimeStep(bool printInfo){
  real_t dt = fmin(_param->Dt(), _dtlimit);
  _geom->Update_U(_u);
  _geom->Update_V(_v);
  MomentumEqu(dt);
  RHS(dt);
  real_t res = 2*_epslimit;
  int it = 0;
  while(res > _epslimit && it < _param->IterMax()){
    _geom->Update_P(_p);
    res = _solver->Cycle(_p,_rhs);
    it = it + 1;
  }  
  NewVelocities(dt);
  _t = _t + dt;
  //TODO PrintInfo Bereich ausprogrammieren.
  if (printInfo)
	{
 		std::cout << "Info: "<< std::endl;
	}
}

/// Returns the simulated time in total
const real_t& Compute::GetTime() const{
  return _t;
}

/// Returns the pointer to U
const Grid* Compute::GetU() const{
  return _u;
}

/// Returns the pointer to V
const Grid* Compute::GetV() const{
  return _v;
}

/// Returns the pointer to P
const Grid* Compute::GetP() const{
  return _p;
}

/// Returns the pointer to RHS
const Grid* Compute::GetRHS() const{
  return _rhs;
}

/// Computes and returns the absolute velocity
const Grid* Compute::GetVelocity(){
  Grid* _vel = new Grid(_geom);
  std::cout<<_geom->Size()[0]<<std::endl;
	//Beim Aufruf von Valid() verwenden wir nicht den Wert, den wir in Next Setzen!!
  for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
    	_vel->Cell(intIt) = sqrt(pow(_u->Cell(intIt), 2) + pow(_v->Cell(intIt) ,2));
	std::cout<<intIt.Valid()<<std::endl;
  }
  return _vel; 
}

/// Computes and returns the vorticity
const Grid* Compute::GetVorticity(){
  Grid* _vor = new Grid(_geom);
  for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
    _vor->Cell(intIt) = _v->dx_l(intIt) - _u->dx_l(intIt); //gibt vorticitiy am Mittelpunkt der Zelle (Rotation der Geschwindigkeit)
	
  }
  return _vor; 
}

/// Computes and returns the stream line values
const Grid* Compute::GetStream(){
  
  return _tmp; //falsch
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
    for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
      _u->Cell(intIt) = _F->Cell(intIt) - dt * _p->dx_r(intIt);
      _v->Cell(intIt) = _G->Cell(intIt) - dt * _p->dy_r(intIt);
    }
  }
  
  /// Compute the temporary velocites F,G
  void Compute::MomentumEqu(const real_t &dt){
    for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
      real_t A = 1/_param->Re() *(_u->dxx(intIt) + _u->dyy(intIt)) - _u->DC_duu_dx(intIt, _param->Alpha()) - _u->DC_dvu_dy(intIt, _param->Alpha(), _v);
      real_t B = 1/_param->Re() *(_v->dxx(intIt) + _v->dyy(intIt)) - _v->DC_dvv_dy(intIt, _param->Alpha()) - _v->DC_duv_dx(intIt, _param->Alpha(), _u);
      _F->Cell(intIt) = _u->Cell(intIt) + dt * A;
      _G->Cell(intIt) = _v->Cell(intIt) + dt * B;
    }
  }
  
  /// Compute the RHS of the poisson equation
  void Compute::RHS(const real_t &dt){
    for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
      _rhs->Cell(intIt) = 1/dt*(_F->dx_l(intIt) + _G->dy_l(intIt));
    }
  }
