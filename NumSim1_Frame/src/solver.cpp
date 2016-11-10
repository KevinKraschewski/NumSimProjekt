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

#include "solver.hpp"
#include "iterator.hpp"
#include "grid.hpp"
#include <math.h>

/// Constructor of the abstract Solver class
Solver::Solver(const Geometry *geom){
  _geom = geom;
}

/// Destructor of the Solver Class
Solver::~Solver(){
  
}


  //const Geometry *_geom;

/// Returns the residual at [it] for the pressure-Poisson equation
real_t Solver::localRes(const Iterator &it, const Grid *grid, const Grid *rhs) const{
  real_t res = 0.0;
  res = -(grid->Cell(it.Left()) + grid->Cell(it.Right()))/pow(_geom->Mesh()[0],2) + (grid->Cell(it.Down()) + grid->Cell(it.Top()))/pow(_geom->Mesh()[1],2) - 2*(pow(_geom->Mesh()[0],2) + pow(_geom->Mesh()[1],2))*grid->Cell(it)/(pow(_geom->Mesh()[0],2) * pow(_geom->Mesh()[1],2)) - rhs->Cell(it);
  return res;
}

  
/// Constructs an actual SOR solver
SOR::SOR(const Geometry *geom, const real_t &omega) : Solver::Solver(geom) {
  _omega = omega;
}

/// Destructor
SOR::~SOR(){
  
}

/// Returns the total residual and executes a solver cycle
// @param grid current pressure values
// @param rhs right hand side
real_t SOR::Cycle(Grid *grid, const Grid *rhs) const{
  real_t totRes = 0.0;
  real_t res = 0.0;
  for(InteriorIterator intIt = InteriorIterator(_geom); intIt.Valid(); intIt.Next()){
    res = localRes(intIt, grid, rhs);
    totRes = totRes + pow(res,2);
    grid->Cell(intIt) = grid->Cell(intIt) - _omega*(pow(_geom->Mesh()[0],2) * pow(_geom->Mesh()[1],2))/(2*(pow(_geom->Mesh()[0],2) + pow(_geom->Mesh()[1],2))) * res;
  }
  return totRes;
}


  //real_t _omega;
