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

#include "grid.hpp"

/// Constructs a grid based on a geometry
Grid::Grid(const Geometry *geom){
  // hier fehlt noch was
}

/// Constructs a grid based on a geometry with an offset
// @param geom   Geometry information
// @param offset distance of staggered grid point to cell's anchor point;
//               (anchor point = lower left corner)
Grid::Grid(const Geometry *geom, const multi_real_t &offset){
  // hier fehlt noch was
}

/// Deletes the grid
Grid::~Grid(){
  // hier fehlt noch was
}

/// Initializes the grid with a value
void Grid::Initialize(const real_t &value){
  // hier fehlt noch was
}

/// Write access to the grid cell at position [it]
real_t Grid::&Cell(const Iterator &it){
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Read access to the grid cell at position [it]
const real_t Grid::&Cell(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Interpolate the value at a arbitrary position
real_t Grid::Interpolate(const multi_real_t &pos) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the left-sided difference quatient in x-dim at [it]
real_t Grid::dx_l(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the right-sided difference quatient in x-dim at [it]
real_t Grid::dx_r(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the left-sided difference quatient in y-dim at [it]
real_t Grid::dy_l(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the right-sided difference quatient in y-dim at [it]
real_t Grid::dy_r(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the central difference quatient of 2nd order in x-dim at [it]
real_t Grid::dxx(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes the central difference quatient of 2nd order in y-dim at [it]
real_t Grid::dyy(const Iterator &it) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes u*du/dx with the donor cell method
real_t Grid::DC_udu_x(const Iterator &it, const real_t &alpha) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes v*du/dy with the donor cell method
real_t Grid::DC_vdu_y(const Iterator &it, const real_t &alpha, const Grid *v) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes u*dv/dx with the donor cell method
real_t Grid::DC_udv_x(const Iterator &it, const real_t &alpha, const Grid *u) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Computes v*dv/dy with the donor cell method
real_t Grid::DC_vdv_y(const Iterator &it, const real_t &alpha) const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Returns the maximal value of the grid
real_t Grid::Max() const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Returns the minimal value of the grid
real_t Grid::Min() const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Returns the absolute maximal value
real_t Grid::AbsMax() const{
  // hier fehlt noch was
  return 0.0; //falsch
}

/// Returns a pointer to the raw data
real_t Grid::*Data(){
  // hier fehlt noch was
  return 0.0; //falsch
}


  //real_t *_data;
  //multi_real_t _offset;
  //const Geometry *_geom;
