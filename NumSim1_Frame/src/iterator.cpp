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
	_valid = this -> Valid();
}

/// Returns the current position value
const index_t& Iterator::Value() const{
  return _value - 1;
}

/// Returns the position coordinates
multi_index_t Iterator::Pos() const{
  multi_index_t position;
  //position[1] = _geom->Size()*(_value%_geom->Length());
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
  
}

/// Checks if the iterator still has a valid value
bool Iterator::Valid() const{
  bool valid = true;
  index_t geo_size = (_geom->Size()[0]+2)*(_geom->Size()[1]+2);
  if (_value > geo_size || _value < 1){
    valid = false;
  }
  return valid;
}

// TODO Prüfen, ob die Werte valid sind...
/// Returns an Iterator that is located left from this one.
// if we are at the left boundary, the cell sees itself
Iterator Iterator::Left() const{
  Iterator *Iterator_left = new Iterator(_geom, _value-1);
  return *Iterator_left;
}

/// Returns an Iterator that is located right from this one
// If we are at the right boundary, the cell sees itself
Iterator Iterator::Right() const{
  Iterator *Iterator_right = new Iterator(_geom, _value+1);
  return *Iterator_right;
}

/// Returns an Iterator that is located above this one
// If we are at the upper domain boundary, the cell sees itself
Iterator Iterator::Top() const{
  Iterator *Iterator_top = new Iterator(_geom, _value+(_geom->Size()[1]));
  return *Iterator_top;
}

/// Returns an Iterator that is located below this one
// If we are at the lower domain boundary, the cell sees itself
Iterator Iterator::Down() const{
  Iterator *Iterator_top = new Iterator(_geom, _value-(_geom->Size()[1]));
  return *Iterator_top;
}


  //const Geometry *_geom;
  //index_t _value;
  //bool _valid;

/// Construct a new InteriorIterator
// Konstruktor von Iterator wird zu Beginn schon aufgerufen, da es keine Konstructor für Iterator ohne Argumente gibt.
InteriorIterator::InteriorIterator(const Geometry *geom) : Iterator::Iterator(geom) {
  // hier fehlt noch was
}

/// Sets the iterator to the first element
void InteriorIterator::First(){
  // hier fehlt noch was
}

/// Goes to the next element of the iterator, disables it if position is end
void InteriorIterator::Next(){
  // hier fehlt noch was
}

/// Constructs a new BoundaryIterator
BoundaryIterator::BoundaryIterator(const Geometry *geom) : Iterator::Iterator(geom) {
  // hier fehlt noch was
}

/// Sets the boundary to iterate
void BoundaryIterator::SetBoundary(const index_t &boundary){
  // hier fehlt noch was
}

/// Sets the iterator to the first element
void BoundaryIterator::First(){
  // hier fehlt noch was
}

/// Goes to the next element of the iterator, disables it if position is end
void BoundaryIterator::Next(){
  // hier fehlt noch was
}


  //index_t _boundary;
