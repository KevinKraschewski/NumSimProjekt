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
#include <iostream>
#include <math.h>
#include "iterator.hpp"

/// Constructs a new Iterator depending on a geometry
Iterator::Iterator(const Geometry *geom){
	_geom = geom;
	_value = 1; // Value ist der Index das Arrays + 1
	_valid = true;
}

/// Constructs a new Iterator on a geometry with a defined starting value
Iterator::Iterator(const Geometry *geom, const index_t &value){
	_geom = geom;
	_value = value;
        _valid = true;
        index_t geo_size = (_geom->Size()[0]+2)*(_geom->Size()[1]+2);
        if (_value > geo_size || _value < 1)
        {
          _valid = false;
        }
}

/// Returns the current position value
const index_t& Iterator::Value() const{
  return _value;
}

/// Returns the position coordinates
multi_index_t Iterator::Pos() const{
  multi_index_t position; //Koordinaten in der Mitte :)
  
  position[0] = (_value-1)%(_geom->Size()[0]+2)+1; // x-Wert
  position[1] = floor((_value-1)/(_geom->Size()[0]+2))+1; // y-Wert
  //Hier...evtl. brauchen wir noch die genauen Angaben... :P
  //position[0] = (_value-1)%(_geom->Size()[0]+2)*_geom->Mesh()[0] - 1/2*_geom->Mesh()[0];
  //position[1] = _geom->Mesh()[1]*(ceil((_value-1)/(_geom->Size()[0]+2))) - 1/2*_geom->Mesh()[1];
  return position; // falsch
}

/// Sets the iterator to the first element
void Iterator::First(){
  _value = 1;
  _valid = true;
}

/// Goes to the next element of the iterator, disables it if position is end
void Iterator::Next(){
  _value = _value + 1;
  index_t geo_size = (_geom->Size()[0]+2)*(_geom->Size()[1]+2);
  if (_value > geo_size || _value < 1)
  {
    _valid = false;
  }
}

/// Checks if the iterator still has a valid value
bool Iterator::Valid() const{
  return _valid;
}

// TODO Prüfen, ob die Werte valid sind...
/// Returns an Iterator that is located left from this one.
// if we are at the left boundary, the cell sees itself
// This ????
Iterator Iterator::Left() const{
    if (_value%(_geom->Size()[0]+2) == 1)
    {
      Iterator *Iterator_left = new Iterator(_geom, _value);
      return *Iterator_left;
    }
    else
    {
      Iterator *Iterator_left = new Iterator(_geom, _value-1);
      return *Iterator_left;
    }
}

/// Returns an Iterator that is located right from this one
// If we are at the right boundary, the cell sees itself
Iterator Iterator::Right() const{
    if (_value%(_geom->Size()[0]+2) == 0)
    {
      Iterator *Iterator_right = new Iterator(_geom, _value);
      return *Iterator_right;
    }
    else
    {
      Iterator *Iterator_right = new Iterator(_geom, _value+1);
      return *Iterator_right;
    }
}

/// Returns an Iterator that is located above this one
// If we are at the upper domain boundary, the cell sees itself
Iterator Iterator::Top() const{
    if (_value>(_geom->Size()[0]+2)*(_geom->Size()[1]+1))
    {
      Iterator *Iterator_top = new Iterator(_geom, _value);
      return *Iterator_top;
    }
    else
    {
      Iterator *Iterator_top = new Iterator(_geom, _value+(_geom->Size()[0]+2));
      return *Iterator_top;
    }
}

/// Returns an Iterator that is located below this one
// If we are at the lower domain boundary, the cell sees itself
Iterator Iterator::Down() const{
    if (_value<=(_geom->Size()[0]+2))
    {
      Iterator *Iterator_down = new Iterator(_geom, _value);
      return *Iterator_down;
    }
    else
    {
      Iterator *Iterator_down = new Iterator(_geom, _value-(_geom->Size()[0]+2));
      return *Iterator_down;
    }
}


  //const Geometry *_geom;
  //index_t _value;
  //bool _valid;

/// Construct a new InteriorIterator
// Konstruktor von Iterator wird zu Beginn schon aufgerufen, da es keine Konstructor für Iterator ohne Argumente gibt.
InteriorIterator::InteriorIterator(const Geometry *geom) : Iterator::Iterator(geom) {
  _value = geom->Size()[0]+4;
  _valid = true;

}

/// Sets the iterator to the first element
void InteriorIterator::First(){
  _value = _geom->Size()[0]+4;
  _valid = true;
}

/// Goes to the next element of the iterator, disables it if position is end
void InteriorIterator::Next(){
    if (this->Pos()[0]== _geom->Size()[0]+1)
    {
      if (this->Pos()[1] == _geom->Size()[1]+1)
        {
          _valid = false;
          //_value = _value+1;  <- WARUM?
        }
        else
        {
          _value = _value + 3;
        }
    }
    else
    {
      _value = _value + 1;
    }

}

/// Constructs a new BoundaryIterator
BoundaryIterator::BoundaryIterator(const Geometry *geom) : Iterator::Iterator(geom) {
  _boundary = 1; //???
}

/// Sets the boundary to iterate
void BoundaryIterator::SetBoundary(const index_t &boundary){
  _boundary = boundary;
}

/// Sets the iterator to the first element
void BoundaryIterator::First(){
  _value = 1;
  _valid = true;
}

/// Goes to the next element of the iterator, disables it if position is end
void BoundaryIterator::Next(){
  if (this->Pos()[1] == 1)
  {
    _value = _value + 1;
  }
  else if (this->Pos()[1]== _geom->Size()[1]+2)
  {
    if (this->Pos()[0] == _geom->Size()[0]+2)
    {
      _valid = false;
      _value = _value +1;
    }
    else
      _value = _value + 1;
  }
  else if (this->Pos()[0] == 1)
  {
    _value = _value + _geom->Size()[0] + 1;
  } 
  else
  {
    _value = _value + 1;
  }
}


  //index_t _boundary;
