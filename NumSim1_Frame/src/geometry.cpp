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

#include "geometry.hpp"

/// Constructs a default geometry:
// driven cavity with 128 x 128 grid, no-slip boundary conditions
// as shown below
//
//      u=1, v=0
//    -------------
//    |           |
// u=0|           |u=0
// v=0|           |v=0
//    |           |
//    |           |
//    -------------
//      u=0, v=0

Geometry::Geometry(){
  // hier fehlt noch was
}

/// Loads a geometry from a file
void Geometry::Load(const char *file){
  // hier fehlt noch was
}

/// Returns the number of cells in each dimension
const multi_index_t Geometry::&Size() const{
  return _size;
}

/// Returns the length of the domain
const multi_real_t Geometry::&Length() const{
  return _legnth;
}

/// Returns the meshwidth
const multi_real_t Geometry::&Mesh() const{
  return _h;
}

/// Updates the velocity field u
void Geometry::Update_U(Grid *u) const{
  // hier fehlt noch was
}

/// Updates the velocity field v
void Geometry::Update_V(Grid *v) const{
  // hier fehlt noch was
}

/// Updates the pressure field p
void Geometry::Update_P(Grid *p) const{
  // hier fehlt noch was
}


  //multi_index_t _size;
  //multi_real_t _length;
  //multi_real_t _h;

  //multi_real_t _velocity;
  //real_t _pressure;
