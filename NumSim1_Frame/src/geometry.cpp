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
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

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
  // Default Geometry:
    index_t x_size = 3;
    index_t y_size = 2;
    _size = {x_size, y_size};

    real_t x_length = 1.0;
    real_t y_length = 1.0;
    _length = {x_length, y_length};

    _pressure = 1.0;
}

/// Loads a geometry from a file
void Geometry::Load(const char *file){
	FILE* handle = fopen(file,"r");
	std::vector<double> inval(2);
	char name[20];
	while (!feof(handle)) {
		if (!fscanf(handle, "%s =", name)) continue;
		if (strcmp(name,"size") == 0) {
			if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
				_size[0] = inval[0];
				_size[1] = inval[1];
			}
			continue;
		}
		if (strcmp(name,"length") == 0) {
			if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
				_length[0] = inval[0];
				_length[1] = inval[1];
			}
			continue;
		}
		if (strcmp(name,"velocity") == 0) {
			if (fscanf(handle," %lf %lf\n",&inval[0],&inval[1])) {
				_velocity[0] = inval[0];
				_velocity[1] = inval[1];
			}
			continue;
		}
		if (strcmp(name,"pressure") == 0) {
			if (fscanf(handle," %lf\n",&inval[0]))
				_pressure = inval[0];
			continue;
		}
	}
	fclose(handle);
}

/// Returns the number of cells in each dimension
const multi_index_t& Geometry::Size() const{
  return _size;
}

/// Returns the length of the domain
const multi_real_t& Geometry::Length() const{
  return _length;
}

/// Returns the meshwidth
const multi_real_t& Geometry::Mesh() const{
  return _h;
}

/// Updates the velocity field u
void Geometry::Update_U(Grid *u) const{
  //Iterator It = Iterator(this, 1);
  //while (It.Pos()[0] == 1)
    
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
