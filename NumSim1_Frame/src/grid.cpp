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
#include "geometry.hpp"
#include "iterator.hpp"
#include <iostream>
#include <math.h>

/// Constructs a grid based on a geometry
Grid::Grid(const Geometry *geom){
  _geom = geom;
  _offset = {0.0, 0.0};
  size = (_geom -> Size()[0]+2)*(_geom -> Size()[1]+2);
  _data = new real_t[size]; //initialisiert ein Array der größe size und setzt _data als Zeiger auf das erste Element
}

/// Constructs a grid based on a geometry with an offset
// @param geom   Geometry information
// @param offset distance of staggered grid point to cell's anchor point;
//               (anchor point = lower left corner)
Grid::Grid(const Geometry *geom, const multi_real_t &offset){
  _geom = geom;
  _offset = offset;
  size = (_geom -> Size()[0]+2)*(_geom -> Size()[1]+2);
  _data = new real_t[size];
}

/// Deletes the grid
Grid::~Grid(){
  delete[] _data;
}

/// Initializes the grid with a value
void Grid::Initialize(const real_t &value){
  for (index_t i=0; i< (_geom -> Size()[0]+2)*(_geom -> Size()[1]+2); i++)
  {
    _data[i] = value;
  }
}

/// Write access to the grid cell at position [it]
real_t& Grid::Cell(const Iterator &it){
  return _data[it-1]; // Durch return wird der Pointer zurueckgegeben und nicht der Wert
}

/// Read access to the grid cell at position [it]
const real_t& Grid::Cell(const Iterator &it) const{
  return _data[it-1];
}


// Interpolate the value at a arbitrary position
real_t Grid::Interpolate(const multi_real_t &pos) const {
  const multi_index_t &size = _geom->Size();
  const multi_real_t &h = _geom->Mesh();

  index_t multSize = 1;
  index_t i = 0;
  multi_real_t delta;
  for(index_t dim = 0; dim < 2; dim++) {
    delta[dim] = (pos[dim] + _offset[dim])/ h[dim] - 1/2;
    index_t iDim = (index_t)( delta[dim] );
    delta[dim] -= iDim;
    i += multSize * iDim;
    multSize *= (size[dim]+2);
  }

  Iterator it(_geom, i+1);
  real_t value = 0;
    value = _data[it-1] * (1.0 - delta[0])*(1.0 - delta[1])
          + _data[it.Right()-1] * delta[0]*(1.0 - delta[1])
          + _data[it.Top()-1] * (1.0 - delta[0])*delta[1]
          + _data[it.Top().Right()-1] * delta[0]*delta[1];

  return value;
}


/*
/// Interpolate the value at a arbitrary position
real_t Grid::Interpolate(const multi_real_t &pos) const{
  real_t interpol = 0.0;
  multi_real_t index = {0.0,0.0};
  multi_real_t distCell = {0.0,0.0};
  index[0] = ceil(pos[0]/(_geom -> Mesh()[0]))+1; //Position der Zelle des Punktes
  index[1] = ceil(pos[1]/(_geom -> Mesh()[1]))+1;
  distCell[0] = pos[0]-(index[0]-1.5)*(_geom -> Mesh()[0]); // Abstand des Punktes zum Mittelpunkt der Zelle
  distCell[1] = pos[1]-(index[1]-1.5)*(_geom -> Mesh()[1]);
  Iterator myIt = Iterator(_geom, index[0] + (index[1]-1) * (_geom->Size()[0]+4)); // Iterator in Zelle des Punktes
  interpol = _data[myIt-1];

  if (_offset[0] == 0.0 && _offset[1] == 0.0){ // Interpolation von p
    if (distCell[0] >= 0 && distCell[1] >= 0){
      interpol = _data[myIt-1]*((_geom->Mesh()[0]-distCell[0])/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Right()-1]*(distCell[0]/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Right().Top()-1]*(distCell[0]/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Top()-1]*((_geom->Mesh()[0]-distCell[0])/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1]);
    } else if (distCell[0] <= 0 && distCell[1] >= 0){
      interpol = _data[myIt-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Top()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Top().Left()-1]*((-distCell[0])/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left()-1]*((-distCell[0])/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1]);
    } else if (distCell[0] <= 0 && distCell[1] <= 0){
      interpol = _data[myIt-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left()-1]*((-distCell[0])/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left().Down()-1]*((-distCell[0])/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Down()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1]);
    } else if (distCell[0] >= 0 && distCell[1] <= 0){
      interpol = _data[myIt-1]*((-distCell[0])/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Down()-1]*((-distCell[0])/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Down().Right()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Right()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1]);
    }
  } else if (_offset[0] == 0.0){ // Interpolation von v
    distCell[1] = distCell[1] - _geom->Mesh()[1]/2;
    if (distCell[0] < 0){
      interpol = _data[myIt-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left()-1]*((-distCell[0])/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left().Down()-1]*((-distCell[0])/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Down()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1]);
    } else {
      interpol = _data[myIt-1]*((-distCell[0])/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Down()-1]*((-distCell[0])/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Down().Right()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Right()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1]);
    }
  } else if (_offset[1] == 0.0){ // Interpolation von u
    
    distCell[0] = distCell[0] - _geom->Mesh()[0]/2;
    if (distCell[1] < 0){
      interpol = _data[myIt-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left()-1]*((-distCell[0])/_geom->Mesh()[0])*(_geom->Mesh()[1]+distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left().Down()-1]*((-distCell[0])/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Down()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((-distCell[1])/_geom->Mesh()[1]);
    } else {
      interpol = _data[myIt-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1])
               + _data[myIt.Top()-1]*(_geom->Mesh()[0]+distCell[0]/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Top().Left()-1]*((-distCell[0])/_geom->Mesh()[0])*(distCell[1]/_geom->Mesh()[1])
               + _data[myIt.Left()-1]*((-distCell[0])/_geom->Mesh()[0])*((_geom->Mesh()[1]-distCell[1])/_geom->Mesh()[1]);
    }
  }

  return interpol;
}
*/

/// Computes the left-sided difference quatient in x-dim at [it]
real_t Grid::dx_l(const Iterator &it) const{
    //TODO Fehler am Ghostand abfangen
  real_t dxL = (_data[it-1] - _data[it-2])/_geom->Mesh()[0];
  return dxL;
}

/// Computes the right-sided difference quatient in x-dim at [it]
real_t Grid::dx_r(const Iterator &it) const{
//TODO Fehler am Ghostand abfangen
  real_t dxR = (_data[it] - _data[it-1])/_geom->Mesh()[0];
  return dxR;
}

/// Computes the left-sided difference quatient in y-dim at [it]
real_t Grid::dy_l(const Iterator &it) const{
  real_t dyL = (_data[it-1] - _data[it.Down()-1])/_geom->Mesh()[1];
  return dyL;
}

/// Computes the right-sided difference quatient in y-dim at [it]
real_t Grid::dy_r(const Iterator &it) const{
  real_t dyR = (_data[it.Top()-1] - _data[it-1])/_geom->Mesh()[1];
  return dyR;
}

/// Computes the central difference quatient of 2nd order in x-dim at [it]
real_t Grid::dxx(const Iterator &it) const{
  real_t dXX = (_data[it]-2*_data[it-1]+_data[it-2])/pow(_geom->Mesh()[0],2);
  return dXX;
}

/// Computes the central difference quatient of 2nd order in y-dim at [it]
real_t Grid::dyy(const Iterator &it) const{
  real_t dYY = (_data[it.Top()-1]-2*_data[it-1]+_data[it.Down()-1])/pow(_geom->Mesh()[1],2);
  return dYY; //Richtig :) :)
}

/// Computes d(u*u)/dx with the donor cell method
real_t Grid::DC_duu_dx(const Iterator &it, const real_t &alpha) const{
    real_t m1 = pow(1/2*(_data[it-1]+_data[it]),2) - pow(1/2*(_data[it-2]+_data[it-1]),2);
    real_t m2 = 1/4*fabs(_data[it-1]+_data[it])*(_data[it-1]-_data[it]) -  1/4*fabs(_data[it-2]+_data[it-1])*(_data[it-2]-_data[it-1]);
    real_t ududx = (1/_geom->Mesh()[0])*m1 + alpha*(1/_geom->Mesh()[0])*m2;
  return ududx;
}

/// Computes d(v*u)/dy with the donor cell method 2.Formel S.25
real_t Grid::DC_dvu_dy(const Iterator &it, const real_t &alpha, const Grid *v) const{
  real_t m1 = (1/4)*((v->Cell(it)+v->Cell(it.Right()))*(_data[it-1]-_data[it.Top()])-(v->Cell(it.Down())+v->Cell((it.Right()).Down())*(_data[it.Down()-1]+_data[it-1])));
  real_t m2 = (1/4)*(fabs(v->Cell(it)+v->Cell(it.Right()))*(_data[it-1]-_data[it.Top()-1])-(fabs(v->Cell(it.Down())+v->Cell(it.Down().Right()))*(_data[it.Down()-1]-_data[it-1])));
  real_t dvudy = (1/_geom->Mesh()[1])*m1 + alpha*(1/_geom->Mesh()[1])*m2;
  return dvudy;
}

/*
/// Computes d(u*v)/dx with the donor cell method
// Hier nochmal drüber schauen.....
real_t Grid::DC_duv_dx(const Iterator &it, const real_t &alpha, const Grid *u) const{
  real_t m1 = (1/4)*((u->Cell(it.Down())+u->Cell(it))*(_data[it-1]+_data[it-2])-(u->Cell(it.Right().Down())+u->Cell(it.Right()))*(_data[it]+_data[it-1]));
  real_t m2 = (1/4)*(fabs(u->Cell(it.Down())+u->Cell(it))*(_data[it-1]-_data[it-2])-fabs(u->Cell(it.Right().Down())+u->Cell(it.Right()))*(_data[it]-_data[it-1]));
  real_t duvdx = (1/_geom->Mesh()[0])*m1 + alpha*(1/_geom->Mesh()[0])*m2; // Evtl. anderstrum ??  
  return duvdx;
}*/

/// Computes d(u*v)/dx with the donor cell method
// Hier nochmal drüber schauen.....
real_t Grid::DC_duv_dx(const Iterator &it, const real_t &alpha, const Grid *u) const{
  real_t m1 = (1/4)*((u->Cell(it.Top())+u->Cell(it))*(_data[it-1]+_data[it])-(u->Cell(it.Left().Top())+u->Cell(it.Left()))*(_data[it-2]+_data[it-1]));
  real_t m2 = (1/4)*(fabs(u->Cell(it.Top())+u->Cell(it))*(_data[it-1]-_data[it])-fabs(u->Cell(it.Top().Left())+u->Cell(it.Left()))*(_data[it-2]-_data[it-1]));
  real_t duvdx = (1/_geom->Mesh()[0])*m1 + alpha*(1/_geom->Mesh()[0])*m2;
  return duvdx;
}

/// Computes d(v*v)/dy with the donor cell method
real_t Grid::DC_dvv_dy(const Iterator &it, const real_t &alpha) const{
  real_t m1 = (1/4)*(pow(_data[it-1]+_data[it.Top()-1],2)-pow(_data[it.Down()-1]+_data[it-1],2));
  real_t m2 = (1/4)*(fabs(_data[it-1]+_data[it.Top()-1])*(_data[it-1]-_data[it.Top()-1])-fabs(_data[it.Down()-1]+_data[it-1])*(_data[it.Down()-1]-_data[it-1]));
  real_t dvvdy = 1/_geom->Mesh()[1]*m1 + alpha*(1/_geom->Mesh()[1])*m2;
  return dvvdy;
}

/// Returns the maximal value of the grid
real_t Grid::Max() const{
  InteriorIterator intIt = InteriorIterator(_geom);
  real_t val = _data[intIt-1];
  real_t valTemp;
  while (intIt.Valid())
  {
      valTemp = _data[intIt-1];
      if (valTemp > val)
      {
          val = valTemp;
      }

      intIt.Next();

  }
  return val;
}

/// Returns the minimal value of the grid
real_t Grid::Min() const{
  InteriorIterator intIt = InteriorIterator(_geom);
  real_t val = _data[intIt-1];
  real_t valTemp;
  while (intIt.Valid())
  {
      valTemp = _data[intIt-1];
      if (valTemp < val)
      {
          val = valTemp;
      }

      intIt.Next();

  }
  return val;
}

/// Returns the absolute maximal value
real_t Grid::AbsMax() const{
  InteriorIterator intIt = InteriorIterator(_geom);
  real_t val = fabs(_data[intIt-1]);
  real_t valTemp;
  while (intIt.Valid())
  {
      valTemp = fabs(_data[intIt-1]);
      if (valTemp > val)
      {
          val = valTemp;
      }

      intIt.Next();

  }
  return val;
}



/// Returns a pointer to the raw data
real_t* Grid::Data(){
  return _data;
}


  //real_t *_data;
  //multi_real_t _offset;
  //const Geometry *_geom;
