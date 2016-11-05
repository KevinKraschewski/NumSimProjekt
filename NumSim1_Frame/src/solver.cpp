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

/// Constructor of the abstract Solver class
Solver::Solver(const Geometry *geom){
  // hier fehlt noch was
}

/// Destructor of the Solver Class
Solver::~Solver(){
  // hier fehlt noch was
}


  //const Geometry *_geom;

/// Returns the residual at [it] for the pressure-Poisson equation
real_t Solver::localRes(const Iterator &it, const Grid *grid, const Grid *rhs) const{
  // hier fehlt noch was
  return 0.0; // falsch
}

  
/// Constructs an actual SOR solver
SOR::SOR(const Geometry *geom, const real_t &omega) : Solver::Solver(geom) {
  // hier fehlt noch was
}

/// Destructor
SOR::~SOR(){
  // hier fehlt noch was
}

/// Returns the total residual and executes a solver cycle
// @param grid current pressure values
// @param rhs right hand side
real_t SOR::Cycle(Grid *grid, const Grid *rhs) const{
  // hier fehlt noch was
  return 0.0; // falsch
}


  //real_t _omega;
